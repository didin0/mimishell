/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:45:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/05 15:52:57 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 pid_t	g_child_pid = -1;

/*
@glance		cmd[] array takes in all node words(tokens) up until redir or pipe
@strdup		is allocating the last level of 3D array cmd
TODO		There are some tangling pointers or something in last cmd layer.
			case cat main.c | grep void | grep list
*/

static void	init_cmd(t_data *data)
{
	int		i;
	int		j;
	t_lexer	*node;

	node = data->lexer_list;
	allocate_cmd(data);
	i = 0;
	j = 0;
	while (node)
	{
		if (j == 0)
			data->cmd[i][j] = NULL;//TODO initalization of a pointer
		if (node->type != PIPE)
			data->cmd[i][j++] = ft_strdup(node->word);
		else
		{
			data->cmd[i][j] = NULL;
			i++;
			j = 0;
		}
		node = node->next;
	}
	data->cmd[i][j] = NULL;
}

/*
@if				check for fork failure
@2nd if			update cur_node in case there are pipes. pipeline mgmt.
*/

static void	resume_parent(t_data *data, pid_t *pids, int i)
{
	if (pids[i] < 0)
	{
//		perror("fork");
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
		exit(EXIT_FAILURE);//TODO free
	}
	if (data->cmd_count > 1)
		update_cur_node(data, i);
	if (data->lexer_list->next)
	{
		if (data->lexer_list->next->type == 400)
			g_child_pid = 2147483647;
		else  
			g_child_pid = pids[i];
	}
//printf("parent IN while @ child in exec g_pid %d - getpid %d -- pids[i] %d\n", g_child_pid, getpid(), pids[i]);
}

/*
@glance			loop token array of arrays, create a child for each array.
@pipefds		allocate pipefd array, read and write ends of pipes.
@paths			compose an array of paths for commands.
@cmd[i]			check for redirections, change the cmd array to take out
				redir tokens and file names. make redirections.
@redir			make pipe fd redirections.
@close			unused fd-s will be closed for child process.
@execve			call command executive file. Normally child exits here.
@parent			close all pipefds for parent pocesss.
 */

void	exec_child(t_env *env_list, t_data *data, pid_t *pids)
{
	int		i;
//	char	**paths;
	int		**pipefd;

	pipefd = create_pipes(data);
	data->paths = organize_good_paths(data, env_list);
	i = 0;
	while (i < data->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			look_for_redirs(data, i);
			redirect_close_fds(data, pipefd, i);
			close_unused_fds(data, pipefd, i);
			if (!exec_builtin_child(data, data->cmd[i], env_list))
				exit(EXIT_SUCCESS);
			else
				if (execve(data->paths[i], data->cmd[i], NULL) == -1)
					ft_error_errno(data, data->cmd[i]);//TODO check
		}
		resume_parent(data, pids, i);
		i++;
	}
//	free_array(paths);no help resolving leaks thus logical 0705 case echo a
	parent_close_all_fds(data, pipefd);
//	free_array(paths);TODO needed but segfults.
}

/*
@design			3 main flows of execution:
				1.builtin in paretn process like exit, export, unset,  cd, $? 
				2. builtin in chilld process like echo, pwd, env 
				3. command to exexcv(), child process, exits by itself
					(data->lexer_list, ASK);

@glance			excecute with token char array in to have builtins return 0 or
				excecutables terminate but keeping the parent process ie
				our shell running.

@meaning		for the cases that do not include a command or builtin
@init_cmd		compose the array of token arrays
@pids			pids have to be an array, for the parerent process to reap
				children correctly.
@keep_cur		keep a list node pointer as static variable, for redirections
				in pipeline. ASSIGN flag means node assigning.
@stat_from		call custom waitpid to store exit statuses. more in signals.c
@global			store child pid in parent process and
				reset child pid after child terminated.
*/

int	execution(t_data *data, t_env *env_list)
{
	pid_t	*pids;

	if (check_meaning(data) != 0)
	{
		add_history(data->line);
		ft_error(data, ERR_MEANING, STDOUT_FILENO, FREE_MEANING);
		return (0);
	}
	init_cmd(data);
	pids = alloc_pids(data);
	keep_cur_node(data->lexer_list, ASSIGN);
	if (!exec_builtin_parent(data, data->cmd[0], env_list))
		return (0);
	else
	{
		exec_child(env_list, data, pids);
		stat_from_waitpid(data, pids);
	}
	g_child_pid = -1;
	free_3D_array(data->cmd);
	free_lexer_list(data);
	free(data->final_path);
//	free_array(data->paths);
	return (0);
}
