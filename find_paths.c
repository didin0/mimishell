/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/05 21:43:28 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		put env PATH into a char ** 
*/

void	get_paths(t_data *data, t_env *env_list)
{
	while (env_list->next)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
		{
			data->paths = ft_split(env_list->value, ':');
			if (!data->paths)
				ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATH);
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

	while (data->paths[i])
	{
		one_path = NULL;
		slash_path = ft_strjoin("/", cmd);
		if (!slash_path)
			ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATH_A);//no free
		one_path = ft_strjoin(data->paths[i], slash_path);
		free(slash_path);
		if (!one_path)
			ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATH_A);//no free
		if (access(one_path, F_OK) == 0)
		{
			data->final_path = malloc(sizeof(char *));
			if (!data->final_path)
				ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_FINAL_PATH);//TODO
			data->final_path = strdup(one_path);//TODO bookmark 060424 flight
			free(one_path);
			if (!data->final_path)
				ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATH_A);
			return (data->final_path);
		}
		i++;
		free(one_path);
	}	
//	free(one_path);
	return (NULL);
}

/*
@glance			compose a char array of arrays of paths for execve
				with the same sequence as cmd array.
*/

char	**organize_good_paths(char ***cmd, t_data *data)
{
	char	**asked_paths;
	int		i;

	asked_paths = ft_calloc(data->cmd_count, sizeof(char *));
	if (!asked_paths)
		ft_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_PATHS);//TODO
	i = 0;
	while (i < data->cmd_count)
	{
		find_good_path(data, cmd[i][0]);
		asked_paths[i] = ft_strdup(data->final_path);
		i++;
	}
	asked_paths[i] = NULL;
	return (asked_paths);
}
