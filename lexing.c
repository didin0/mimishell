/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:00:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/01 07:12:55 by rsainas          ###   ########.fr       */
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

void	str_to_list(t_data *data, t_stat *stat, char *buff)
{
	if (stat->i == stat->ibis)
		return ;
	if (data->line)
		buff = ft_substr(data->line, stat->ibis, stat->i - stat->ibis);
	if (!buff)
		ft_error(data);//TODO
	ft_lstlex_add_back(&data->lexer_list, ft_lstlex_new(buff));
}

/*
@glance			loop leading space, loop each char in line.
				append tokens to a list.
@var			ibis is the first unporcessed character and i the last 
 				char of a word.
@is_token		token here is a redirection or a pipe,
				store substring to buffer.
@ft_lstlex_		append node with buffer string to the list
@elseif ' '		space inidcates next token, add to list, deal wiht line end.
@elseif '"'		makes list node from quoted token. 
				first and second quote found, 
				update i to the second quote char.
*/

static void	splitting_lexer(t_data *data, t_stat *stat)
{
	char	*buff;
	int		ret;

	ret = 0;
	buff = NULL;
	while (data->line && data->line[stat->i] == ' ')
		stat->i++;
	stat->ibis = stat->i;
	while (data->line && data->line[stat->i])
	{
		if (is_token(data->line, stat->i) || data->line[stat->i] == '\0')
			create_node_is_token(data, stat, buff);
		else if (data->line[stat->i] == ' ' || data->line[stat->i + 1] == '\0')
			ret = create_node_space_term(data, stat, buff);
		else if (data->line[stat->i] == '"' || data->line[stat->i] == '\'')
			ret = create_node_quotes(data, stat, buff);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
		stat->i++;
	}
}

void	lexing(t_data *data)
{
	t_stat	stat;

	data->lexer_list = ft_calloc(sizeof(t_lexer), 1);
	if (!data->lexer_list)
		ft_error(data);
	stat.i = 0;
	stat.ibis = 0;
	splitting_lexer(data, &stat);
	if (!data->lexer_list)
		ft_error(data);
}
