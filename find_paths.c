/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/30 08:07:59 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_data *data, t_env *env_list)
{
	char	**paths;
	char	*path;

	while (env_list->next)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
		{
			paths = ft_split(env_list->value, ':');
			if (!paths)
				ft_error(data);//TODO free ft_split malloc failed.
		}
		env_list = env_list->next;
	}
	return (paths);
}

/*
@glance		loop all env PATH paths with lexer list words TODO
*/

char	*find_good_path(t_data *data, char *cmd, char **paths)
{
	char	*one_path;
	char	*tmp;
	int		i;

	one_path = malloc(sizeof(char *));
	tmp = malloc(sizeof(char *));
	if (!one_path || !tmp)
		ft_error(data);//TODO free, malloc fail
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", cmd);
		one_path = ft_strjoin(paths[i], tmp);
		if (!one_path)
			ft_error(data);//TODO malloc fail from ft_strjoin
		if (access(one_path, F_OK) == 0)
			return (one_path);
		i++;
	}
	return (NULL);
}

/*
@glance			compose a char array of arrays of paths for execve
				with the same sequence as cmd array.
*/

char	**organize_good_paths(char ***cmd, t_data *data, t_env *env_list)
{
	char	**all_paths;
	char	*one_good_path;
	char	**asked_paths;
	int		i;

	all_paths = get_paths(data, env_list);
	asked_paths = ft_calloc(data->cmd_count, sizeof(char *));
	if (!asked_paths)
		ft_error(data);//TODO malloc fail msg, clean exti
	i = 0;
	while (i < data->cmd_count)
	{
		one_good_path = find_good_path(data, cmd[i][0], all_paths);
		asked_paths[i] = one_good_path;
		i++;
	}
	return (asked_paths);
}
