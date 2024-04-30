/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:52:39 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/29 20:29:02 by rsainas          ###   ########.fr       */
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

/*
@glance		count two types at the time.
*/

int	count_token_type(t_data *data, int type1, int type2)
{
	t_lexer	*temp;
	int		count;

	temp = data->lexer_list;
	count = 0;
	while (temp->next)
	{
		if (temp->type == type1 || temp->type == type2)
			count++;
		temp = temp->next;
	}
	if (temp->type == type1 || temp->type == type2)
		count++;
	return (count);
}

/*
@glance		keeps the offset in linked list to seperate string arrays
			for execution() while loop, to manage the pipline.
*/

t_lexer	*keep_cur_node(t_lexer *cur_node, int i)
{
	static t_lexer	*temp;

	if (i == ASSIGN)
		temp = cur_node;
	return (temp);
}

/*
@glance		parent process keeping track of the current node, for child process
			to know to make redirections.
@i			child number
*/

void	update_cur_node(t_data *data, int i)
{
	t_lexer	*node;
	int		j;

	node = data->lexer_list;
	j = -1;
	while (node && j < i)
	{
		if (node->type == PIPE)
		{
			node = node->next;
			keep_cur_node(node, ASSIGN);
			j++;
		}
		node = node->next;
	}
}

/*
@glance				waitpid retunrs child PID or - 1
@W UNTRACED			wait for processes status change, get status
@W IFEXITED			check if the process exited normally ie by exit()
@W EXITSTATUS		macro to extract the exit satus of waitpid
@W IFSIGLAED		was the child killed by a signal, add 128 to status
*/

void	stat_from_waitpid(t_data *data, pid_t *pids)
{
	int	i;
	int	status;
	int	cmd_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	i = 0;
	while (i < cmd_count)
	{
		if ((waitpid(pids[i], &status, WUNTRACED)) == -1)
			perror("waitpid");
//		ft_error(data);//TODO free on waitpid fail
		i++;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
	free(pids);
}
