/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:00:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/30 12:33:37 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		Split the user input into multiple node and put it in a linked list.
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

int	str_to_list(t_data *data, char *buff, char *line, int i, int ibis)
{
	if (i == ibis)
		return (0);
	if (line)
		buff = ft_substr(data->line, ibis, i - ibis);
	if (!buff)
		return (0);
	ft_lstlex_add_back(&data->lexer_list, ft_lstlex_new(buff));
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

static void	splitting_lexer(t_data *data, char *line)
{
	int		i;
	int		ibis;
	char	*buff;

	i = 0;
	ibis = 0;
	buff = NULL;
	while (line && line[i] == ' ')
		i++;
	ibis = i;
	while (line && line[i])
	{
//		create_node_is_token(data, i, ibis, buff);//i and ibis need return
		if (is_token(line, i) || line[i] == '\0')
		{
			if (ibis != i)
			{
				if (str_to_list(data, buff, line, i, ibis) != 0)
					return ;
			}
			if (is_token(line, i) == 2)
			{
				buff = ft_substr(line, i, 2);
				if (!buff)
					return ;
				i++;
			}
			else
				buff = ft_substr(line, i, 1);
			if (!buff)
				return ;
			ft_lstlex_add_back(&data->lexer_list, ft_lstlex_new(buff));
			while (line[i + 1] == ' ')
				i++;
			ibis = i + 1;
		}
		else if (line[i] == ' ' || line[i + 1] == '\0')
		{
			if (line[i + 1] == '\0')
			{
				if (line[i] != ' ')
					i++;
				if (str_to_list(data, buff, line, i, ibis) != 0)
					return ;
				break ;
			}
			if (str_to_list(data, buff, line, i, ibis) != 0)
				return ;
			while (line [i + 1] == ' ' && line[i + 1] != '\0')
				i++;
			ibis = i + 1;
			if (line[i + 1] == ' ')
				continue ;
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			if (is_quote_closed(line, line[i]) != 0)
				ft_error(data);//TODO exit, no free
			i = ft_strchr_end(line, line[i], i) + 1;
			while ((line[i] != '\0' && is_token(line, i) == 0) && line[i] != ' ')
				i++;
			if (str_to_list(data, buff, line, i, ibis) != 0)
				return ;
			if (line[i] == '\0')
				break ;
			if (line[i + 1] == '\0' || is_token(line, i) != 0 || line[i] == ' ')
			{
				ibis = i;
				continue ;
			}
			else
				ibis = i + 1;
		}
		i++;
	}
}

void	lexing(t_data *data)
{
	data->lexer_list = ft_calloc(sizeof(t_lexer), 1);
	if (!data->lexer_list)
		ft_error(data);
	splitting_lexer(data, data->line);
	if (!data->lexer_list)
		ft_error(data);
}
