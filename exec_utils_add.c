/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/03 13:11:09 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance				alloc one cmd array with the size of token list.
@if !cmd[i][j]		in case allocation partially fails, 
					free all previously alloc.	
*/
/*
static void	allocate_cmd_arrays(t_data *data, int i)
{
	int		j;

	j = 0;
	while (j < data->list_size)
	{
		data->cmd[i][j] = ft_calloc(1001, sizeof(char));
		if (!data->cmd[i][j])
		{
			while (--i >= 0)
				free_array(data->cmd[i]);
			free(data->cmd);
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO msg Allocation fail cmd array, exit
		}
		j++;
	}
	data->cmd[i][j] = NULL;//terminating 2D array
}
*/
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

*/

void	allocate_cmd(t_data *data)
{
//	char	***cmd;
	int		i;

	data->list_size = adv_list_size(data->lexer_list);
	data->cmd = malloc((data->cmd_count + 1) * sizeof(char **));
	if (!data->cmd)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO msg Allocation fail cmd array, exit
	i = 0;
	while (i < data->cmd_count)
	{
		data->cmd[i] = malloc((data->list_size + 1) * sizeof(char *));
		if (!data->cmd[i])
		{
			while (--i >= 0)
				free_array(data->cmd[i]);
			free(data->cmd);
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO msg Alloc fail cmd array, free cmd[i]!!, exit
		}
//		allocate_cmd_arrays(data, i);
		i++;
	}
	data->cmd[data->cmd_count] = NULL;//TODO terminating 3D array
}

/*
@ifs		in case there are no pipes, pipefd[0] needs to be initializedi
*/

int	**create_pipes(t_data *data)
{
	int	**pipefd;
	int	pipe_count;
	int	j;

	pipe_count = count_token_type(data, PIPE, EMPTY);
	pipefd = malloc((pipe_count + 1) * sizeof(int *));
	if (!pipefd)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO msg Allocation fail, exit
	j = 0;
	while (j < pipe_count)
	{
		pipefd[j] = malloc(2 * sizeof(int));
		if (!pipefd[j])
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO msg Allocation fail, exit
		pipe(pipefd[j]);
		j++;
	}
	if (j > 0)
		pipefd[j] = NULL;
	if (j == 0)
		pipefd[0] = NULL;
	return (pipefd);
}

pid_t	*alloc_pids(t_data *data)
{
	pid_t	*pids;

	pids = malloc(data->cmd_count * sizeof(pid_t));
	if (!pids)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);//TODO put to data->
//		ft_error(data);//TODO msg Allocation faily, exit
	return (pids);
}

int	adv_strncmp(const char *s1, const char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s1))
		&& !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (0);
	return (1);
}
