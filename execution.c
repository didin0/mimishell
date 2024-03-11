/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:45:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/11 19:16:39 by rsainas          ###   ########.fr       */
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
@dev		cmd[] array has all node, thus should have one cmd and its args
 * */

char	**get_cmd(t_lexer *lexer_list)
{
	char	**cmd;
	int		i;

	cmd = ft_calloc((list_size(lexer_list) + 1), (sizeof(char *)));//TODO calloc fail
	i = 0;
	while (lexer_list)
	{
		cmd[i] = ft_strdup(lexer_list->word);//ft_strdup need here, lexer_list is on heap
		lexer_list = lexer_list->next;
		i++;
	}
	return (cmd);
}

/*
@glance		loop all env PATH paths with all lexer list words TODO
 *
 * */
char    *find_good_path(char **cmd, char **paths)
{
    char *path = malloc(sizeof(char *));//TODO fail, assign
    char *tmp = malloc(sizeof(char *));//TODO fail, assign
    int i = 0;

    while(paths[i])
    {
        tmp = ft_strjoin("/", cmd[0]);
        path = ft_strjoin(paths[i], tmp);
        if(access(path, F_OK) == 0)
            return path;
        else
            free(path);
        i++;
    }
    return NULL;//TODO free tmp;
}

void	execution(t_data *data, t_env *env_list)
{
	char	**cmd;
    char    **paths;
    char    *path;
	pid_t	pid1;

	int code;

    paths = get_paths(env_list);
	cmd = get_cmd(data->lexer_list);
    path = find_good_path(cmd, paths);
//	printf("number of pipes %d\n", count_tokens(data, PIPE));//number times the exec loops need to run
	pid1 = fork();//TODO protect fork return -1 
	if (pid1 == 0)
	{
    	execve(path, cmd, NULL);
	}
	else
		stat_from_waitpid(data, pid1);
//	printf("Exit status cmd %d\n", data->exit_status);
	return;
}
