/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:45:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/23 07:56:26 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *env_list)
{
	char	**paths;
	char	*path;

	while (env_list->next)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
			paths = ft_split(env_list->value, ':');//ft_split return char **
		env_list = env_list->next;
	}
	return (paths);
}

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
@glance		cmd[] array takes in all node words up until redir or pipe
*/

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

/*
@glance		loop all env PATH paths with all lexer list words TODO
*/

char    *find_good_path(char **cmd, char **paths)
{
    char *path = malloc(sizeof(char *));//TODO fail, assign
    char *tmp = malloc(sizeof(char *));//TODO fail, assign
    int i = 0;

    while(paths[i])
    {
        tmp = ft_strjoin("/", cmd[0]);
        path = ft_strjoin(paths[i], tmp);
		free(tmp);
        if(access(path, F_OK) == 0)
            return path;
        else
            free(path);
        i++;
    }
    return NULL;//TODO free tmp;
}

int	execution(t_data *data, t_env *env_list)
{
	char	**cmd;
    char    **paths;
    char    *path;
	pid_t	pid1;

	t_lexer	*cur_node;//TODO sone too many
	int code;

    paths = get_paths(env_list);
	cmd = get_cmd(data, data->lexer_list);	
	cur_node = keep_cur_node(data->lexer_list, ASK);
	pid1 = fork();//TODO protect fork return -1 
	if (pid1 == 0)
	{
		if (is_token(cur_node->word, 0))
				make_redirections(data, cur_node);
		path = find_good_path(cmd, paths);
		if (is_builtin(data, cmd[0]))
			exec_builtin(data, cmd, env_list);
		else
		{
			if (execve(path, cmd, NULL) == -1)
				ft_error_errno(data, cmd[0]);
		}
	}
	else
		stat_from_waitpid(data, pid1);
	keep_cur_node(data->lexer_list, ASSIGN);//reset static variable
	return (0);
}
