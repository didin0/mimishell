/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:45:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/22 15:32:13 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_child_pid = -1;

int	list_size(t_lexer *lexer_list)
{
	int	i;

	i = 0;
	while (lexer_list)
	{
		i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}

/*
 * 			put everithing in the list exept the pipes
@glance		cmd[] array takes in all node words up until redir or pipe
*/

static	char	***init_cmd(t_data *data)
{
	char	***cmd;
	int		i;
	int		j;
	t_lexer *node;

	node = data->lexer_list;
	cmd = allocate_cmd(data);
	i = 0;
	j = 0;
	while (node)
	{
		if (node->type != PIPE)
			cmd[i][j++] = node->word; 
		else
		{
			i++;
			j = 0;
		}
		node = node->next;
	}
	return (cmd);
}

/*	
char	**get_cmd(t_data *data, t_lexer *lexer_list)
{
	char	**cmd;
	int		i;
	t_lexer *cur_node;

	cur_node = lexer_list;
	cmd = ft_calloc((list_size(cur_node) + 1), (sizeof(t_lexer *)));//TODO calloc fail
	i = 0;
	while (cur_node->next)
	{
		if (is_token(cur_node->word, 0) && peek_list_from(cur_node)
				&& cur_node->next->next)//in case more 
		{
			if (cur_node->type == REDIR_OUT)
				create_empty_file(data, cur_node->next->word);
			cur_node = cur_node->next->next;//traverse 2 nodes
		}
		else if (is_token(cur_node->word, 0))//in case token
			break;
		cmd[i] = ft_strdup(cur_node->word);
//		printf("char **cmd where I look at cmd[i] %c \n", cmd[i][2]); 
		cur_node = cur_node->next;
		i++;
	}
	if (cur_node && !is_token(cur_node->word, 0))//in case only one token in cmd
		cmd[i] = ft_strdup(cur_node->word);
	if (!is_token(cur_node->word, 0))
	{
		cmd[i] = ft_strdup(cur_node->word);
	}
	keep_cur_node(cur_node, ASSIGN);
	return (cmd);
}
*/
/* OUTDATED
@glance			excecute with token char array in child process to have
				excecutables terminate but keeping the parent process ie
				our shell running.
@400			special case to handle SIGINT inside heredoc
@global			store child pid in parent process and
				restore child pid after child terminated.
@stat_from		call custom waitpid to store exit statuses. more in signals.c
*/

int		bypass_child(t_data *data, char ***cmd, t_env *env_list)
{
	if (is_builtin(data, cmd[0][0]))//current node logic needs redone.
	{
		if (exec_builtin(data, cmd[0], env_list) == 0);//not checking return!!
			return (1);
	}
//	if (ft_strncmp(data->lexer_list->word, "$?",
//	}
//	ft_strlen(data->lexer_list->word)))
	return (0);
}

/*
@glance		3 main flows of execution:
			1. command to exexcv(), child process, exits by itself
			2. builtin in chilc process, we call exit
			3. cd and exit builtin in parent process, return (0)
*/

int	execution(t_data *data, t_env *env_list)
{
	char	***cmd;
    char    *path;
	pid_t	*pids;

	if (check_meaning(data) != 0)
	{
		printf("meaning missing\n");
//		ft_error(data);//TODO msg no meaning/command missing
		return (0);
	}
	cmd = init_cmd(data);
	data->cmd = cmd;//TODO is this still needed??
	pids = alloc_pids(data);
	keep_cur_node(data->lexer_list, ASSIGN);//initialize the cur_node, for redis
//	do redirections for the first cmd array.
	if(bypass_child(data, cmd, env_list))
		return (0);
	else
	{
		exec_child(cmd, env_list, data, pids);
		stat_from_waitpid(data, pids);
	}
	g_child_pid = -1;
	return (0);
}
// why should the redirections be within child process at all
// the complexity is keeping a cur_node in and out of child process
void	exec_child(char ***cmd, t_env *env_list, t_data *data, pid_t *pids)
{	
//	int	cmd_count;
	int	i;
	char **paths;
	int		**pipefd;
	t_lexer	*cur;

	pipefd = create_pipes(data);
//	cmd_count = count_token_type(data, BUILTIN, COMMAND); 	
	paths =	organize_good_paths(cmd, data, env_list);
	i = 0;
	while (i < data->cmd_count) 
	{
		pids[i] = fork();//TODO protection needed
		if (pids[i] == 0) 
		{
//			if (is_token(cur_node->word, 0))//redir does not have a node pointed
//			if (array_contains_redir(cmd[i], data))
//			{
//				printf("I found a redir\n");
		keep_cur_node(data->lexer_list, ASK);
			cmd[i] = look_for_redirs(cmd[i], data, i);
//			show_cmd(&cmd[i], data);	
//			make_redirections(data, cur_node);// same here!!!
//			}
			redirect_close_fds(data, pipefd, i);//no pipe???
			close_unused_fds(data, pipefd, i);
			if (execve(paths[i], cmd[i], NULL) == -1)
				{
					printf("execve retunring -1\n");
				 	ft_error_errno(data, cmd[i]);
				}
		}
		else if (pids[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (data->cmd_count > 1)//there is a pipe
			update_cur_node(data, i);
	cur = keep_cur_node(data->lexer_list, ASK);
//	printf("cur node %s,  end of cmd[%d] \n", cur->word, i); 
		i++;
	}
	parent_close_all_fds(data, pipefd);
	if (data->lexer_list->type == 400)
			g_child_pid = 2147483647;
		else
			g_child_pid = pids[i];//TODO need incrementation, chech signals
}

/*
@glance			excecute with token char array in child process to have
				excecutables terminate but keeping the parent process ie
				our shell running.
@400			special case to handle SIGINT inside heredoc
@global			store child pid in parent process and
				restore child pid after child terminated.
@stat_from		call custom waitpid to store exit statuses. more in signals.c
*/
/*
int	execution(t_data *data, t_env *env_list, char **envp)
{
	char	**cmd;
    char    **paths;
    char    *path;
	pid_t	pid1;

	t_lexer	*cur_node;//TODO one too many variables
    
	paths = get_paths(env_list);
	cmd = get_cmd(data, data->lexer_list);	
	data->cmd = cmd;
//	printf("cmd gets $? %s\n", cmd[0]);
	cur_node = keep_cur_node(data->lexer_list, ASK);
//	printf("cur node has$? %s type %d\n", cur_node->word, cur_node->type);//word not written node
	if (ft_strncmp(data->lexer_list->word, "$?",
				ft_strlen(data->lexer_list->word)))//do not for in case $?
//else the $? is sent to execve and it trigers a SIGSEV signal
	{
		pid1 = fork();//TODO protect fork return -1 
		if (pid1 == 0)
		{
			if (is_token(cur_node->word, 0))
				make_redirections(data, cur_node);// same here!!!
			path = find_good_path(cmd, paths);
			if (is_builtin(data, cmd[0]))
				exec_builtin(data, cmd, env_list, envp);//not checking return!!!
			else
			{
			 if (execve(path, cmd, NULL) == -1)
			 	ft_error_errno(data, cmd[0]);
			}
		}
		else
		{
			if (data->lexer_list->type == 400)
				g_child_pid = 2147483647;
			else
				g_child_pid = pid1;
			stat_from_waitpid(data, pid1);
//			g_parent_pid = getpid();//dev
		}
	}
	g_child_pid = -1;
	keep_cur_node(data->lexer_list, ASSIGN);//reset static variable
	return (0);
}*/
