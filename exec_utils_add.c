/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/01 12:36:21 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		alloc one cmd array with the size of token list.
*/

static void	allocate_cmd_arrays(t_data *data, char ***cmd, int i)
{
	int		j;

	data->list_size = adv_list_size(data->lexer_list);
	j = 0;
	while (j < data->list_size + 1)
	{
		cmd[i][j] = ft_calloc(1, sizeof(char));
		if (!cmd[i][j])
			ft_error(data);//TODO msg Allocation fail cmd array, exit
		j++;
	}
}

/*
@glance		cmd is a pointer to an array of char arrays. The array of arrays
			is null terminated for execve and loop safety.
*/

char	***allocate_cmd(t_data *data)
{
	char	***cmd;
	int		i;

	cmd = ft_calloc(data->cmd_count + 1, sizeof(char **));
	if (!cmd)
		ft_error(data);//TODO msg Allocation fail cmd array, exit
	i = 0;
	while (i < data->cmd_count + 1)
	{
		cmd[i] = ft_calloc(1, sizeof(char *));
		if (!cmd[i])
			ft_error(data);//TODO msg Alloc fail cmd array, free cmd[i]!!, exit
		allocate_cmd_arrays(data, cmd, i);
		i++;
	}
	cmd[i - 1] = NULL;
	return (cmd);
}

int	**create_pipes(t_data *data)
{
	int	**pipefd;
	int	pipe_count;
	int	j;

	pipe_count = count_token_type(data, PIPE, EMPTY);
	pipefd = malloc((pipe_count) * sizeof(int *));
	if (!pipefd)
		ft_error(data);//TODO msg Allocation fail, exit
	j = 0;
	while (j < pipe_count)
	{
		pipefd[j] = malloc(2 * sizeof(int));
		if (!pipefd)
			ft_error(data);//TODO msg Allocation fail, exit
		pipe(pipefd[j]);
		j++;
	}
	return (pipefd);
}

pid_t	*alloc_pids(t_data *data)
{
	pid_t	*pids;
	int		cmd_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	pids = malloc(cmd_count * sizeof(pid_t));
	if (!pids)
		ft_error(data);//TODO msg Allocation faily, exit
	return (pids);
}

int	adv_strncmp(const char *s1, const char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s1))
		&& !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (0);
	return (1);
}
