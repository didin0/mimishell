/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:45:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/07 18:11:36 by mabbadi          ###   ########.fr       */
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
			paths = ft_split(env_list->value, ':');
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

char	**get_cmd(t_lexer *lexer_list)
{
	char	**cmd;
	int		i;

	cmd = ft_calloc((list_size(lexer_list)), (sizeof(char *)));
	i = 0;
	while (lexer_list)
	{
		cmd[i] = ft_strdup(lexer_list->word);
		lexer_list = lexer_list->next;
		i++;
	}
	return (cmd);
}
char    *find_good_path(char **cmd, char **paths)
{
    char *path = malloc(sizeof(char *));
    char *tmp = malloc(sizeof(char *));
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
    return NULL;
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
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("path : |%s|\n", path);
		printf("cmd[0] : |%s|\n", cmd[0]);
    	execve(path, cmd, NULL);
	}
	else
		waitpid(pid1, NULL, 0);
	return;
}
