/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:34:33 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/24 14:15:31 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_close_all_fds(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->pipe_count)
	{
		close(data->pipefd[j][0]);
		close(data->pipefd[j][1]);
		j++;
	}
}

void	redirect_close_fds(t_data *data, int i)
{
	if (i > 0)
	{
		dup2(data->pipefd[i - 1][0], STDIN_FILENO);
		close(data->pipefd[i - 1][0]);
	}
	if (i < data->pipe_count)
	{
		dup2(data->pipefd[i][1], STDOUT_FILENO);
		close(data->pipefd[i][1]);
	}
}

/*
Exmaple to illustrate the pattern of fd-s in a pipeline.

Child		0		1			2		3		4
pipefd[0]  r W		R w	   r w	   r w 	   r w
pipefd[1]  r w		r W	   R w	   r w 	   r w
pipefd[2]  r w		r w	   r W	   R w 	   r w
pipefd[3]  r w		r w	   r w	   r W 	   R w

So close all lowercase fd-s, duplicate and then close uppercase fd-s.
*/

void	close_unused_fds(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->pipe_count)
	{
		if (i - j != 1)
			close(data->pipefd[j][0]);
		if (i != j)
			close(data->pipefd[j][1]);
		j++;
	}
}
