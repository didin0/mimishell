/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/04 21:20:21 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
all paths
main -> ctrl-D, !data.line //no leaks
main : linebeak -> ctrl-D 2nd if //no leaks
main : spaces -> ctrl-D // no leaks
main : asd -> lexing -> lexer_list = NULL // no leaks

*/
void	free_env_list(t_env *head)
{
	t_env *node;
	
	while (head)
	{
		node = head;
		head = head->next;
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	free_lexer_list(t_data *data)
{
	t_lexer *node;
	
	while (data->lexer_list)
	{
		node = data->lexer_list;
		data->lexer_list = data->lexer_list->next;//TODO
		free(node->word);
		free(node);
	}
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}
//should I write malloc fails also to fd 2???
void	ft_error(t_data *data, const char *msg, int fd, int flag)
{
	if (flag != FREE_ENV)
		if (ft_putstr_fd("Error: ", fd) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
	if (flag != 0)
	{
		if (ft_putstr_fd((char *)msg, fd) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
	}
	if (flag != FREE_LINE_RET && flag != FREE_MEANING)	
		free_env_list(data->env_list);
	if (flag != FREE_ENV)	
		free(data->line);
	if ((flag != FREE_LINE && flag != FREE_ENV) && flag != FREE_MEANING)	
		rl_clear_history();
	if (((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET))	
		free_lexer_list(data);
	if (((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET)
			&& flag != FREE_LIST)
		free(data->buff);
	if ((((((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET)
		&& flag != FREE_LIST) && flag != FREE_NAMES) && flag != FREE_PATH)
		&& flag != FREE_MEANING)
			free_array(data->builtin_names);//all the next ones since this is freed
	if ((((((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET)
		&& flag != FREE_LIST) && flag != FREE_NAMES) && flag != FREE_PATH)
		&& flag != FREE_MEANING)
			free_array(data->all_paths);//starting form FREE_PATH_ALL
	if (flag != FREE_LINE_RET && flag != FREE_MEANING)
		exit(EXIT_FAILURE);
}

/*
@glance		child process writes only to STDOUT	
@caution	if the error message gets written 2 times seamingly to stdout
			then run the ./minishell 2>err.log
			effectivlely sending the stderr stream to a log file.
			could be becuase we are running a shell with a shell.
*/

void	ft_error_errno(t_data *data, char **cmd)
{

	write(STDERR_FILENO, *cmd, ft_strlen(*cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(EXIT_FAILURE);//TODO free data
}
