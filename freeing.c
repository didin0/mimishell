/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/24 21:11:16 by rsainas          ###   ########.fr       */
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

static void ft_error_cont(t_data *data,  int flag)
{
	if (flag == FREE_PAR_RE)
		free(data->remaining);
	if (((flag == FREE_PARSER || flag == FREE_PAR_NEW) && flag != FREE_PAR_RES)
		&& flag != FREE_PAR_RES_1)
	{
		free(data->result);
		free(data->new_str);
	}
	if (flag == FREE_CMD_1 || flag == EX_ARG || flag == FREE_NEW_ENV)
		free_3D_array(data->cmd);
	if (flag == FREE_PIDS || flag == EX_ARG || flag == FREE_NEW_ENV
			|| flag == FREE_CHIL)
		free(data->pids);
	if (flag == FREE_NEW_ENV)
		free_array(data->new_env);
	if (flag == FREE_CHIL)
	{
		free_array(data->paths);
		free_array(data->asked_paths);
		free_int_array(data->pipefd);
	}
	if (flag == CD_ARG || flag == CD_HOME || flag == CD_PWD)	
		free_regular(data);

}

static void ft_error_add(t_data *data,  int flag)
{
	if (flag != FREE_NAMES_P && flag != FREE_ONE)//path_a in use??
		free_array(data->builtin_names);
	if (flag != FREE_NAMES_P && flag != FREE_NAMES_A)//names_a in use??
		free_array(data->paths);
	if ((((flag != FREE_NAMES_P && flag != FREE_NAMES_A) && flag != FREE_NAMES)
			&& flag != FREE_PATHS) && flag != FREE_SLASH)//names_a in use??
	{
		free_3D_array(data->cmd);
		free(data->pids);
		free_array(data->asked_paths);
		free_int_array(data->pipefd);
	}
	if ((((flag != FREE_NAMES_P && flag != FREE_NAMES) && flag != FREE_PATHS)
		&& flag!= FREE_SLASH) && flag != FREE_ONE)
		free(data->final_path);
	if ((flag != FREE_LINE_RET && flag != FREE_MEANING) && flag != EX_ARG)//TODO
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
	if (((flag != FREE_LINE_RET && flag != FREE_MEANING) && flag != FREE_0)
		&& flag != CD_ARG)
		free_env_list(data->env_list);
	if (flag != FREE_ENV)
	{
		data->exit_status = 127;//TODO, is this exit status for all errors ok.
		free(data->line);
	}
	if (((flag != FREE_LINE && flag != FREE_ENV) && flag != FREE_MEANING)
			&& flag != CD_ARG)	
		rl_clear_history();
	if (((flag != FREE_ENV && flag != FREE_LINE) && flag != FREE_LINE_RET)
		&& flag != FREE_0)
		free_lexer_list(data);
	ft_error_cont(data, flag);
	if (((((((flag > 7 && flag != EX_ARG) && flag != FREE_NEW_ENV)
		&& flag != FREE_CHIL) && flag != CD_ARG) && flag != FREE_0)
		&& flag != CD_HOME) && flag != CD_PWD)
		ft_error_add(data, flag);
//TODO meaning is bigger than 7 check if meaing is freed properly
	if (((flag != FREE_LINE_RET && flag != FREE_MEANING) && flag != EX_ARG)
		&& flag != CD_ARG)//TODO
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
