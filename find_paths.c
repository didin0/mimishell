/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/27 13:06:52 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		put env PATH into a char ** 
*/

void	get_paths(t_data *data, t_env *env_list)
{
	data->paths = NULL;
	while (env_list->next)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
		{
			data->paths = ft_split(env_list->value, ':');
			if (!data->paths)
				ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_NAMES);
			break ;
		}
		env_list = env_list->next;
	}
}

/*
@glance				loop all env PATH paths with lexer list words TODO
@return(NULL)		path not valid.
@var				if a static variable is assigned a NULL by ft_strjoin
					this needs to freeing in ft_error().
*/

char	*find_good_path(t_data *data, char *cmd)
{
	int		i;
	char *slash_path;
	char *one_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
	{
		data->final_path = cmd;
		return (data->final_path);
	}
	(void)cmd;
	while (data->paths[i])
	{
		one_path = NULL;
		slash_path = ft_strjoin("/", cmd);
		if (!slash_path)
			ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATHS);
		one_path = ft_strjoin(data->paths[i], slash_path);
		free(slash_path);
		if (!one_path)
			ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_SLASH);
		if (access(one_path, F_OK) == 0)
		{
			data->final_path = NULL;
			data->final_path = strdup(one_path);
			free(one_path);
			if (!data->final_path)
				ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_ONE);
			return (data->final_path);
		}
		i++;
		free(one_path);
	}	
	return (NULL);
}

/*
@glance			compose a char array of arrays of paths for execve
				with the same sequence as cmd array.
*/

void	organize_good_paths(t_data *data, t_env *env_list)
{
//	char	**asked_paths;
	int		i;

	data->asked_paths = ft_calloc(data->cmd_count + 1, sizeof(char *));
	if (!data->asked_paths)
		ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATHS);//TODO
	i = 0;
//	if (!data->paths)
		get_paths(data, env_list);//TODO note in case of env, pwd
	while (i < data->cmd_count)
	{
		find_good_path(data, data->cmd[i][0]);
		data->asked_paths[i] = ft_strdup(data->final_path);
		free(data->final_path);
		i++;
	}
	data->asked_paths[i] = NULL;	
//	return (asked_paths);
}
