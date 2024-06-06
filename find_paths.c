/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 22:42:29 by rsainas          ###   ########.fr       */
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
				adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
			re_bin(data->paths, 0);
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
you can give abs path within the executive folder.
*/

char	*find_good_path(t_data *data, char *cmd)
{
	int		i;
	char *slash_path;
	char *one_path;

	i = 0;

	data->final_path = NULL;
	while (data->paths[i])
	{
		one_path = NULL;
		slash_path = ft_strjoin("/", cmd);
		if (!slash_path)
			adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
		re_bin(slash_path, 0);
		if (!is_token_path(cmd))
			one_path = strdup(cmd); 
		else
			one_path = ft_strjoin(data->paths[i], slash_path);
		if (!one_path)
			adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
		re_bin(one_path, 0);
		if (access(one_path, F_OK) == 0)
		{
			data->final_path = NULL;
			data->final_path = strdup(one_path);
			if (!data->final_path)	
				adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
			re_bin(data->final_path, 0);
			return (data->final_path);
		}
		i++;
	}	
	return (NULL);
}

/*
@glance			compose a char array of arrays of paths for execve
				with the same sequence as cmd array.
*/

void	organize_good_paths(t_data *data, t_env *env_list)
{
	int		i;

	data->asked_paths = ft_calloc(data->cmd_count + 1, sizeof(char *));
	if (!data->asked_paths)
		adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
	re_bin(data->asked_paths, 0);
	i = 0;
		get_paths(data, env_list);
	while (i < data->cmd_count && data->lexer_list->type != EXP_STATUS)
	{
		find_good_path(data, data->cmd[i][0]);
		data->asked_paths[i] = ft_strdup(data->final_path);
		if (!data->asked_paths[i])
			adv_error(data, ERR_MALLOC_PATH, STDERR_FILENO, FREE_M);	
		re_bin(data->asked_paths[i], 0);
		i++;
	}
	data->asked_paths[i] = NULL;	
}
