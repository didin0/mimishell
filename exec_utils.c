/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:52:39 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/16 17:49:29 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		number of commands = number of pipes - 1
*/

int	count_token_type(t_data *data, int	type1, int type2)
{
	t_lexer	*temp;
	int	count;

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
 * !!!!!! DOES NOT CHECK THE LAST NODE TODO
@glance		number of commands = number of pipes - 1
*/

int	count_tokens(t_data *data)
{
	t_lexer	*temp;
	int	count;

	temp = data->lexer_list;
	count = 0;
	while (temp != NULL)
	{
		if (is_token(temp->word, 0))
			count++;
		temp = temp->next;
	}
	return (count);
}
/*
@glance		keeps the offset in linked list to seperate string arrays
			for execution() while loop.
*/

t_lexer	*keep_cur_node(t_lexer *cur_node, int i)
{
	static t_lexer *temp = NULL;

	if (i == ASSIGN)
		temp = cur_node;
	return (temp);
}

/*
@dev		debugging function
@glance		print a non terminated string array
*/

void	print_str_array(char **array, int len)
{
	int	i;

	if (array)
	{
		i = 0;
		write(1, "String array:\n", 13); 
		while (i < len)
		{
			write(1, array[i], ft_strlen(array[i]));//TODO return -1
			write(1, "--", 2);
			i++;
		}
		write(1, "\n", 1);
	}
	return;
}

/*
@glance				waitpid retunrs child PID or - 1
					127 is the exit status value in case $? and again $?
@W UNTRACED			wait for processes status change, get status
@W IFEXITED			check if the process exited normally ie by exit()
@W EXITSTATUS		macro to extract the exit satus of waitpid
@W IFSIGLAED		was the child killed by a signal, add 128 to status
*/

void stat_from_waitpid(t_data *data, pid_t *pids)
{
	int i;
	int	status;
	int	cmd_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND); 
	i = 0;
	while (i < cmd_count)
	{	
		if ((waitpid(pids[i], &status, WUNTRACED)) == -1)
			perror("waitpid");
//		ft_error(data);//TODO
		i++;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);	
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
	free(pids);
	return;//redundant TODO;
}
/*
void stat_from_waitpid(t_data *data, pid_t pid1)
{
	int	status;

	if ((waitpid(pid1, &status, WUNTRACED)) == -1)
		perror("waitpid");
//		ft_error(data);//TODO
	else
	{
		if (WIFEXITED(status))
		{
			data->exit_status = WEXITSTATUS(status);	
		}
		else if (WIFSIGNALED(status))
		{
			data->exit_status = 128 + WTERMSIG(status);
		}
	}
	return;
}*/
