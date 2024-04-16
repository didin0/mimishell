/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:34:33 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/16 17:49:31 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_close_all_fds(t_data *data, int **pipefd)
{
	int	pipe_count;
	int	j;

	pipe_count = count_token_type(data, PIPE, EMPTY);
	j = 0;
	while (j < pipe_count)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		free(pipefd[j]);
		j++;
	}
	free(pipefd);
}

void	redirect_close_fds(int **pipefd, int num_commands, int i)
{
	if (i > 0)
  	{ // Not the first command, dup the read side fd-s
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][0]);
	}
	if (i < num_commands - 1) 
	{ // Not the last command, dup the write side fd-s
		dup2(pipefd[i][1], STDOUT_FILENO);
		close(pipefd[i][1]);
	}
}

/*
 *
 *
Exmaple
Child		0		1	 	2		3		4
pipefd[0]  r W	   R w	   r w	   r w 	   r w
pipefd[1]  r w	   r W	   R w	   r w 	   r w
pipefd[2]  r w	   r w	   r W	   R w 	   r w
pipefd[3]  r w	   r w	   r w	   r W 	   R w

so close all lowercase fd-s, duplicate and then close uppercase fd-s.
*/

void	close_unused_fds(int **pipefd, int num_commands, int i)
{
	int	j;

	j = 0;
	while (j < num_commands - 1)
	{
		if (i - j != 1)
			close(pipefd[j][0]);//close read fd-s
		if (i != j)
			close(pipefd[j][1]);//close write fd-s
		j++;
	}
}
