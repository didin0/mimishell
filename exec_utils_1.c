/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/18 17:00:14 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	are_too_many_arguments(char ***cmd)
{
	int	i;
	int args;
	
	args = 0;
	while (cmd[i])//loop each array
	{
		if (cmd[i
	
	
	}


}*/

char ***allocate_cmd(t_data *data)
{
	char ***cmd;
	int	cmd_count;
	int	i;

	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	cmd = ft_calloc(cmd_count, sizeof(char**));
	if (!cmd)
		ft_error(data);//TODO msg Allocation fail cmd array, exit
	i = 0;
	while (i < cmd_count)
	{
		cmd[i] = ft_calloc(MAX_ARGS_CMD + 1, sizeof(char*)); 
		if (!cmd[i])
			ft_error(data);//TODO msg Alloc fail cmd array, free cmd[i]!!, exit
		i++;
	}
	cmd[i] = NULL;
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
	int	cmd_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND); 
	pids = malloc(cmd_count * sizeof(pid_t));
	if (!pids)
		ft_error(data);//TODO msg Allocation faily, exit
	return (pids);
}

int	peek_list_from(t_lexer *node)
{
	t_lexer *temp;
	int peek_type;

	peek_type = node->type;
	temp = node->next;
	while (temp->next)
	{		
		if (temp->type == peek_type)//type found
			return (1);	
		temp = temp->next;
	}
	return (0);//did not find or @ tail node
}
