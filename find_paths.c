/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/18 08:39:18 by rsainas          ###   ########.fr       */
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

/*
@glance		loop all env PATH paths with all lexer list words TODO
*/

char    *find_good_path(t_data *data, char *cmd, char **paths)
{
	char	*one_path;
	char	*tmp;
	int i;

    one_path = malloc(sizeof(char *));//TODO fail, assign
    tmp = malloc(sizeof(char *));//TODO fail, assign
	if (!one_path || !tmp)
			ft_error(data);//TODO malloc fail
	i = 0;
 	while(paths[i])
    {
        tmp = ft_strjoin("/", cmd);
        one_path = ft_strjoin(paths[i], tmp);
		if (!one_path)
			ft_error(data);//TODO malloc fail from ft_strjoin
        if (access(one_path, F_OK) == 0)
            return (paths[i]);
//		else
//			free(paths);//TODO free array of arrays needed
		i++;
	}
	return (NULL);
}

/*
@glance			compose a char array of arrays of paths for execve
				with the same sequence as cmd array.
*/

char **organize_good_paths(char ***cmd, t_data *data, t_env *env_list)
{
	char **all_paths;
	char *one_good_path;
	char **asked_paths;
	int	cmd_count;
	int i;

	
	all_paths = get_paths(env_list);
	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	asked_paths = ft_calloc(cmd_count, sizeof(char *));
	if (!asked_paths)
		ft_error(data);// malloc fail msg, clean exti
	i = 0;
	while (i < cmd_count)
	{
		one_good_path = find_good_path(data, cmd[i][0], all_paths);
//		if (!one_good_path)
//			ft_error(data);//TODO free paths malloced in find_good_path
		asked_paths[i] = one_good_path;
		i++;
	}
	return (asked_paths);
}
