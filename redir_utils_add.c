/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:41:16 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/26 19:41:39 by rsainas          ###   ########.fr       */
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
				&& node->type != EXP_STATUS)
			&& node->type != 31) && node->type != 32)
		node = node->next->next;
	return (node);
}

/*OUT OF DATE
@2nd if		in case there are several redirection within one cmd array
@3rd if		expand the exit status for 
@NULL		set the last pointer in cmd pointer array to NULL for
			execve() and safe looping.
*/

void	clean_cmd_from_redir(t_data *data, t_lexer *node, int i)
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
