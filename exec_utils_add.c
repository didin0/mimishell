/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/21 16:23:05 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance			cmd is a pointer to an array of char arrays. The array of arrays
				is null terminated for execve and loop safety.

3D array		outer layer is char*** that has blocks size of char** to the
				amount of cmd_count.
				middle layer is char ** that has block sixe of char * to the
				amount of tokens until pipe.
				deepest layer is a char *.
@if !cmd[i]		in case allocation partially fails, free all previously alloc.
???				in case of echo a I have 2 arrays allocated cmd_count+1
@NULL			terminating 3D array, to array level
*/

void	allocate_cmd(t_data *data)
{
	int	i;

	data->list_size = adv_list_size(data->lexer_list);
	data->cmd = malloc((data->cmd_count + 1) * sizeof(char **));
	if (!data->cmd)
		adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_M);
	i = 0;
	re_bin(data->cmd, 0);
	while (i < data->cmd_count)
	{
		data->cmd[i] = malloc((data->list_size + 1) * sizeof(char *));
		if (!data->cmd[i])
			adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_M);
		re_bin(data->cmd[i], 0);
		i++;
	}
	data->cmd[data->cmd_count] = NULL;
}

/*
@ifs		in case there are no pipes, pipefd[0] needs to be initializedi
*/

void	create_pipes(t_data *data)
{
	int	j;

	data->pipefd = malloc((data->pipe_count + 1) * sizeof(int *));
	if (!data->pipefd)
		adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_ENV);
	re_bin(data->pipefd, 0);
	j = 0;
	while (j < data->pipe_count)
	{
		data->pipefd[j] = malloc(2 * sizeof(int));
		if (!data->pipefd[j])
			adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_ENV);
		re_bin(data->pipefd[j], 0);
		if (pipe(data->pipefd[j]) == -1)
			adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_ENV);
		j++;
	}
	if (j > 0)
		data->pipefd[j] = NULL;
	if (j == 0)
		data->pipefd[0] = NULL;
}

void	alloc_pids(t_data *data)
{
	data->pids = malloc(data->cmd_count * sizeof(pid_t));
	if (!data->pids)
		adv_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_M);
	re_bin(data->pids, 0);
}

int	adv_strncmp(const char *s1, const char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s1)) && !ft_strncmp(s1, s2,
			ft_strlen(s2)))
		return (0);
	return (1);
}
