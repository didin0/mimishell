/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:15:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/21 18:47:23 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		re-assignes redirection tokens. uppon malloc failure,
			exits child process.
*/

static void	reassign_str(t_data *data, int i, int k, char *new_str)
{
	data->cmd[i][k] = re_bin(ft_strdup(new_str), 0);
	if (!data->cmd[i][k])
		adv_error(data, ERR_MALLOC_RE_U, STDERR_FILENO, FREE_M);
}

static t_lexer	*clean_cmd_loop(t_lexer *node)
{
	if (((is_token(node->word, 0) && node->type != EXP_STATUS)
			&& node->type != 31) && node->type != 32)
		node = node->next->next;
	if (((((node && is_token(node->word, 0)) && node->type != PIPE)
				&& node->type != EXP_STATUS) && node->type != 31)
		&& node->type != 32)
		node = node->next->next;
	return (node);
}

/*OUT OF DATE
@2nd if		in case there are several redirection within one cmd array
@3rd if		expand the exit status for
@NULL		set the last pointer in cmd pointer array to NULL for
			execve() and safe looping.
*/

static void	clean_cmd_from_redir(t_data *data, t_lexer *node, int i)
{
	int	k;

	k = 0;
	while (node && node->type != PIPE)
	{
		node = clean_cmd_loop(node);
		if (!node)
			break ;
		if (node && node->type != PIPE)
			reassign_str(data, i, k, node->word);
		if (node->type == PIPE)
		{
			data->cmd[i][k] = NULL;
			i++;
			k = 0;
		}
		else
			k++;
		node = node->next;
	}
	data->cmd[i][k] = NULL;
}

/*
@2nd if		in case there is a pipeline, the cur node is not the first node
 */

void	change_cmd(t_data *data, int i)
{
	t_lexer	*node;
	int		j;

	node = NULL;
	node = keep_cur_node(node, ASK);
	j = 0;
	if (node != data->lexer_list)
	{
		node = data->lexer_list;
		while (node && j < i)
		{
			if (node->type == PIPE)
				j++;
			node = node->next;
		}
		keep_cur_node(node, ASSIGN);
	}
	clean_cmd_from_redir(data, node, i);
}

void	array_contains_redir(t_data *data)
{
	t_lexer	*node;

	node = data->lexer_list;
	node = keep_cur_node(node, ASK);
	while (node && node->type != PIPE)
	{
		if (is_token(node->word, 0))
		{
			if (node->type == REDIR_OUT || node->type == REDIR_OUT_APP
				|| node->type == REDIR_IN)
				redir_fd(data, node);
			else if (node->type == HERE_DOC)
				here_doc_in(data, node);
		}
		node = node->next;
	}
}
