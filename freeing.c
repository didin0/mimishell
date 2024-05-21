/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/21 11:06:57 by rsainas          ###   ########.fr       */
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
		data->lexer_list = data->lexer_list->next;
		free(node->word);
		free(node);
	}
	
}

/*
free a null terminated 3D char array
*/

void	free_3D_array(char ***str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			free_array(str[i++]);
	}
	free(str);
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

void	free_int_array(int **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

static void ft_error_add(t_data *data,  int flag)
{
	if (flag != FREE_NAMES && flag != FREE_PATH_A)
		free_array(data->builtin_names);
	if ((flag != FREE_NAMES && flag != FREE_NAMES_A) && flag != FREE_PATH)
		free_array(data->paths);
	if ((((flag != FREE_NAMES && flag != FREE_NAMES_A) && flag != FREE_PATH)
		&& flag!= FREE_FINAL_PATH) && flag != FREE_PATH_A)
		free(data->final_path);
//	if (((flag != FREE_NAMES && flag != FREE_NAMES_A) && flag != FREE_PATH)
//		&& flag != FREE_ONE_PATH_A)
//		free(data->slash_path);
	

//	if (flag != FREE_PATHS && flag != FREE_NAMES_A)
//			free_array(data->all_paths);
	if (flag != FREE_LINE_RET)//TODO
		exit(EXIT_FAILURE);
}

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
	if ((((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET)
			&& flag != FREE_LIST) && flag != FREE_MEANING)
		free(data->buff);
	if (flag > 7)
		ft_error_add(data, flag);
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
	(void)data;
	write(STDERR_FILENO, *cmd, ft_strlen(*cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(EXIT_FAILURE);//TODO free data
}
