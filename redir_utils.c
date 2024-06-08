/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:15:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/27 13:43:16 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	adv_list_size(t_lexer *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static void	reassign_str(t_data *data, int i, int k, char *new_str)
{
	if (data->cmd[i][k])
		free(data->cmd[i][k]);
	data->cmd[i][k] = ft_strdup(new_str);
	if (!data->cmd[i][k])
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);//TODO
//	free(new_str);//TODO has no effect.
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
	int l;

	k = 0;
	l = 0;
	while (node && node->type != PIPE)
	{
		if (is_token(node->word, 0) && node->type != EXP_STATUS)
			node = node->next->next;
		if (((node && is_token(node->word, 0)) && node->type != PIPE)
			&& node->type != EXP_STATUS)
			node = node->next->next;
		if (!node)
			break ;
		if (node && node->type == EXP_STATUS)
		{
			data->cmd[i][k] = ft_itoa(data->exit_status);
			node = node->next;
			k++;
		}
		if (node && node->type != PIPE)
			reassign_str(data, i, k, node->word);
//		if (node)//TODO was for a special case. 
//			reassign_str(data, i, k, node->word);
		if (node->type == PIPE)
		{
			l = k;
			while (data->cmd[i][l])
				free(data->cmd[i][l++]);
			data->cmd[i][k] = NULL;
			i++;
			k = 0;
		}
		else
			k++;
		node = node->next;
	}
	l = k;//TODO new function
	while (data->cmd[i][l])
		free(data->cmd[i][l++]);
	data->cmd[i][k] = NULL;
}

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
