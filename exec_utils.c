/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:52:39 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/11 19:15:44 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
@glance		number of commands = number of pipes - 1
*/

int	count_tokens(t_data *data, int token)
{
	t_lexer	*temp;
	int	count;

	temp = data->lexer_list;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == token)
			count++;
		temp = temp->next;
	}
	return (count);
}

/*
@glance				waitpid retunrs child PID or - 1
					127 is the exit status value in case $? and again $?
@W UNTRACED			wait for processes status change, get status
@W IFEXITED			check if the process exited normally ie by exit()
@W EXITSTATUS		macro to extract the exit satus of waitpid
@W IFSIGLAED		was the child killed by a signal, add 128 to status
*/

void stat_from_waitpid(t_data *data, pid_t pid1)
{
	int	status;

	data->exit_status = 127;
//	printf("Exit init status cmd %d\n", data->exit_status);
	if ((waitpid(pid1, &status, WUNTRACED)) == -1)
		printf("Error: waitpid() failed\n");
//		ft_error(data);//TODOi
	else
	{
		if (WIFEXITED(status))
		{
			data->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			data->exit_status = 128 + WTERMSIG(status);//TODO testing if signals impl
		}
	}
	return;
}
