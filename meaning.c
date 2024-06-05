/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:36:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/05 10:25:47 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_data *data)
{
	t_env *temp;

	temp = data->env_list;
	while (temp)
	{
		if (!adv_strncmp(temp->key, "PATH"))
			return (0);
		temp = temp->next;
	}
	ft_error(data, ERR_PATH, STDOUT_FILENO, FREE_LINE_RET);
	return (1);
}

/*
@glance		for the cases that do not include a command or builtin
*/

int	check_meaning(t_data *data)
{
	t_lexer *node;

	node = data->lexer_list;
	data->cmd_count = count_token_type(data, BUILTIN, COMMAND);
	data->pipe_count = count_token_type(data, PIPE, EMPTY);
	if (node)
	{
		if (node->type == EXP_STATUS && !node->next)
			data->cmd_count = 1;
		if (node->type == BUILTIN && !adv_strncmp(node->word, "cd"))
			data->cmd_count = 1;
		else if (node->next && (node->type == COMMAND
			&& node->next->type == HERE_DOC))
		{
			if (node->next->next && (node->next->next->type == COMMAND
					|| node->next->next->type == BUILTIN))
				data->cmd_count = data->cmd_count - 1;//cat << cat | grep a == missing meaning
			else if (node->next->next)
				data->cmd_count = data->cmd_count;// cat << cat several children
		}
	}
	if (data->cmd_count == 0 || (data->cmd_count != data->pipe_count + 1))
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

