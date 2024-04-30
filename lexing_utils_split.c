/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:23:41 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/30 12:36:11 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	create_node_is_token(t_data *data, int i, int ibis, char *buff)
{
	if (is_token(line, i) || line[i] == '\0')
	{
	if (ibis != i)
	{
		if (str_to_list(data, buff, line, i, ibis) != 0)
			return;
	}
	if (is_token(line, i) == 2)
	{
		buff = ft_substr(line, i, 2);
		if (!buff)
			return;
		i++;
	}
	else
		buff = ft_substr(line, i, 1);
	if (!buff)
		return;
	ft_lstlex_add_back(&data->lexer_list, ft_lstlex_new(buff));
	while (line[i + 1] == ' ')
		i++;
	ibis = i + 1;
	}
}*/
