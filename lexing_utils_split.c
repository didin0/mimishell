/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:23:41 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/22 17:30:52 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		creates a node to linked list where the line includes token ie
			a metacharacter.
*/

void	create_node_is_token(t_data *data, t_stat *stat)
{
	if (stat->ibis != stat->i)
		str_to_list(data, stat);
	if (is_token(data->line, stat->i) == 2)
	{
		data->buff = ft_substr(data->line, stat->i, 2);
		if (!data->buff)
			ft_error(data, ERR_MALLOC_LUS, STDERR_FILENO, FREE_LIST);
		stat->i++;
	}
	else
		data->buff = ft_substr(data->line, stat->i, 1);
	if (!data->buff)
		ft_error(data, ERR_MALLOC_LUS, STDERR_FILENO, FREE_LIST);
	ft_lstlex_add_back(&data->lexer_list, ft_lstlex_new(data, data->buff));
	while (data->line[stat->i + 1] == ' ')
		stat->i++;
	stat->ibis = stat->i + 1;
}

/*
@glance		creates a node to linked list where the line includes spaces or
			lexer is at the end of the line.
@return		return 1 indicates a break to the main lexing loop and 2 continue.
*/

int	create_node_space_term(t_data *data, t_stat *stat)
{
	if (data->line[stat->i + 1] == '\0')
	{
		if (data->line[stat->i] != ' ')
			stat->i++;
		str_to_list(data, stat);
		return (1);
	}
	str_to_list(data, stat);
	while (data->line [stat->i + 1] == ' '
		&& data->line[stat->i + 1] != '\0')
		stat->i++;
	stat->ibis = stat->i + 1;
	if (data->line[stat->i + 1] == ' ')
		return (2);
	return (0);
}

/*
@glance			creates a node to linked list where the line includes quotes
				single or double ones.
@return			return 1 indicates a break to the main lexing loop
				and 2 continue.
@ft_strchr_end	look for second char " or ' in line, return char pos.
*/

int	create_node_quotes(t_data *data, t_stat *stat)
{
	stat->i = ft_strchr_end(data->line,
			data->line[stat->i], stat->i) + 1;
	while ((data->line[stat->i] != '\0' && is_token(data->line,
				stat->i) == 0) && data->line[stat->i] != ' ')
		stat->i++;
	str_to_list(data, stat);
	if (data->line[stat->i] == '\0')
		return (1);
	if (data->line[stat->i + 1] == '\0'
		|| is_token(data->line, stat->i) != 0
		|| data->line[stat->i] == ' ')
	{
		stat->ibis = stat->i;
		return (2);
	}
	else
		stat->ibis = stat->i + 1;
	return (0);
}
