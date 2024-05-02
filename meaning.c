/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:36:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/02 14:03:07 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		for the cases that do not include a command or builtin
*/

int	check_meaning(t_data *data)
{
	int	cmd_count;
	int	pipe_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	pipe_count = count_token_type(data, PIPE, EMPTY);
	data->cmd_count = cmd_count;
	data->pipe_count = pipe_count;
	if (data->lexer_list->type == 6 && !data->lexer_list->next)
		data->cmd_count = 1;
	if (data->cmd_count == 0)
		return (1);
	return (0);
}

int	check_heredoc_meaning(t_lexer *node)
{
	if (node->next)
		if (node->next->type != OTHER)
			return (1);
	return (0);	
}

