/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:00:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/14 12:47:38 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
			Split the user input into multiple node and put it in a linked list.
			The user input is splited in a node when it occur an escape ' '.
			If the user input contain chars : '|' or '>' or '<' or '>>' or '<<'
			The input is splitted and the token is placed in a separated node.
@general	If the token size is known then we use the is_token() else
			we use splitting_lexer()
*/

int	is_token(char *c, int i)
{
	if (c[i] == '|')
		return (1);
	else if (c[i] == '<' || c[i] == '>')
	{
		if (c[i] == '<' && c[i + 1] == '<')
			return (2);
		if (c[i] == '>' && c[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	else if (c[i] == '$' && c[i + 1] == '?')
		return (2);
	return (0);
}

int	add_substr_to_list(t_lexer **lexer_list, char *buff, char *line, int i,
		int ibis)
{
	if (i == ibis)
		return (0);
	if(line)
		buff = ft_substr(line, ibis, i - ibis);
	if (!buff)
		return (0);
	ft_lstlex_add_back(lexer_list, ft_lstlex_new(buff));
	return (0);
}

/*
@glance			loop leading space, loop each char in line.
				return list of tokens.
@var			ibis is the first unporcessed character and i the last 
 				char of a word.
@is_token		token here is a redirection or a pipe
@if is_token	makes list nodes from redirections and pipe
				ibis !=i ......TODO
				if redir, store substring to buffer
@ft_lstlex_		append node with buffer string to the list
@elseif ' '		space inidcates next token, add to list, deal wiht line end.
@elseif '"'		makes list node from double quoted token.
				first and second quote found, 
				update i to the second quote char.
@ft_strchr_end	look for second char " or ' in line, return char pos.
*/

t_lexer	*splitting_lexer(char *line, t_lexer **lexer_list)
{
	int		i;
	int		ibis;
	char	*buff;
//	int		aff;

	i = 0;
	ibis = 0;
	buff = NULL;

//	printf("initial line %s, last char %d\n", line, line[3]);
	while (line && line[i] == ' ')	
		i++;
	ibis = i;
	while (line && line[i])
	{
		if (is_token(line, i) || line[i] == '\0')
		{
			if (ibis != i)
			{
//				printf("node created by ibis != i ???? \", from ibis %d to i %d \n", ibis, i);
				if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
					return (NULL);
			}
			if (is_token(line, i) == 2)
			{
				buff = ft_substr(line, i, 2);
				if (!buff)
					return (NULL);
				i++;
			}
			else
				buff = ft_substr(line, i, 1);
			if (!buff)
				return (NULL);
//			printf("node created by is_token, return 1 2, from ibis %d to i %d\n", ibis, i);
			ft_lstlex_add_back(lexer_list, ft_lstlex_new(buff));
			while (line[i + 1] == ' ')
				i++;
			ibis = i + 1;
		}
		else if (line[i] == ' ' || line[i + 1] == '\0') 
		{
			if (line[i + 1] == '\0')
			{
				if (line[i] != ' ')
					i++;//to put the last char on line to node
//				printf("node created by terminator \\0, from ibis %d to i %d \n", ibis, i);
				if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
					return (NULL);
				break ;
			}
//			printf("node created by space, from ibis %d to i %d \n", ibis, i);
			if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
				return (NULL);
			while (line [i + 1] == ' ' && line[i + 1] != '\0')//handle preceeding spaces
				i++;	
			ibis = i + 1;
			if (line[i + 1] == ' ')
				continue;
		}
		else if (line[i] == '"' || line[i] == '\'')
		{	 
			if (is_quote_closed(line, line[i]) != 0)
				printf("-------------------quote not closed!!!!----------------\n");
//				ft_error(data);TODO exit, further not needed to be handled by subj
			i = ft_strchr_end(line, line[i], i) + 1;
//			printf("entering  while\", ibis %d to i %d -- %d \n", ibis, i, line[i]);
			while ((line[i] != '\0' && is_token(line, i) == 0) && line[i] != ' ')
				i++;
//			printf("node created by double \", from ibis %d i %d -- %d \n", ibis, i, line[i]);
			if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
				return (NULL);
			if (line[i] == '\0')// case "a"
				break;
			if (line[i + 1] == '\0' || is_token(line, i) != 0 || line[i] == ' ')//case "a">|
			{
				ibis = i;
				continue;		
			}
			else
				ibis = i + 1;// all other cases where I return to main loop "a"> asd
		}
		i++;//any other char
//		printf("main loop ibis %d to i %d -- %d \n", ibis, i, line[i]);
	}
	return (*lexer_list);
}

void	lexing(t_data *data)
{
	data->lexer_list = ft_calloc(sizeof(t_lexer), 1);
	if (!data->lexer_list)
		ft_error(data);
	data->lexer_list = splitting_lexer(data->line, &data->lexer_list);
	if (!data->lexer_list)
		ft_error(data);
}

