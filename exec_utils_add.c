/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/24 12:42:41 by rsainas          ###   ########.fr       */
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
	int		i;

	data->list_size = adv_list_size(data->lexer_list);
	data->cmd = malloc((data->cmd_count + 1) * sizeof(char **));
	if (!data->cmd)
		ft_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_PAR_RES);
	i = 0;
	while (i < data->cmd_count)
	{
		data->cmd[i] = malloc((data->list_size + 1) * sizeof(char *));
		if (!data->cmd[i])
		{
			while (--i >= 0)
				free_array(data->cmd[i]);
			free(data->cmd);
			ft_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_PAR_RES);
		}
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
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO msg Allocation fail, exit
	j = 0;
	while (j < data->pipe_count)
	{
		data->pipefd[j] = malloc(2 * sizeof(int));
		if (!data->pipefd[j])
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO msg Allocation fail, exit
		pipe(data->pipefd[j]);
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
		ft_error(data, ERR_MALLOC_EX_UA, STDERR_FILENO, FREE_CMD_1);
}

int	adv_strncmp(const char *s1, const char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s1))
		&& !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (0);
	return (1);
}
