/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:15:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 21:54:35 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@2nd if		in case there is a pipeline, the cur node is not the first node
 */

static void	change_cmd(t_data *data, int i)
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

static void	array_contains_redir(t_data *data)
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

/*
@glance		look for redirection tokens, adjust the cmd
*/

void	look_for_redirs(t_data *data, int i)
{
	array_contains_redir(data);
	change_cmd(data, i);
}
