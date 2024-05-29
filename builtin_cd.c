/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:20:38 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/24 19:27:38 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*our_get_env(t_env *env_list, char *env)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, env, ft_strlen(env)))
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	return (temp->value);
}

/*
@ft_strdup		elliminates shared memory, when func concecutivelly called.
				repreated calls to func will lead to temp->value pointing to
				same memory location for both paths, leading to shared memory
*/

static void	change_env(t_data *data, t_env *env_list, char *env, char *path)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, env, ft_strlen(env)))
		{
			free(temp->value);
			temp->value = ft_strdup(path);
			if (!temp->value)
				ft_error(data, ERR_MALLOC_BU_CD, STDERR_FILENO, FREE_NEW_ENV);
		}
		temp = temp->next;
	}
	(void)path;//TODO
}

static void	get_abs_path(t_data *data, t_env *env_list)
{
	char	abs_path[PATH_MAX];//TODO, what size is needed

	change_env(data, env_list, "OLDPWD", our_get_env(env_list, "PWD"));
	if (getcwd(abs_path, sizeof(abs_path)) != NULL)
		change_env(data, env_list, "PWD", abs_path);
	else
		ft_error(data, ERR_CD_GET, STDERR_FILENO, CD_PWD);
	if (data->pwd_flag == 1)
		pwd_builtin(data, env_list);
	data->pwd_flag = 0;
}

/*
@ft_strl		copy home path, concatenate cd first argument skipping tilde 
*/

static void	expand_tilde(t_data *data, char **cmd, t_env *env_list)
{
	char	*new_path;
	char	*home;
	size_t	new_len;

	if (cmd[2])
		ft_error(data, ERR_CD_MAX, STDERR_FILENO, CD_ARG);
	else if (cmd[1][1] == '\0' || cmd[1][1] == '/'
				|| !ft_strncmp(cmd[1], "~/.", 3))
		{
			home = our_get_env(env_list, "HOME");
			new_path = malloc(ft_strlen(home) + ft_strlen(cmd[1]));
			if (!new_path)
				ft_error(data, ERR_MALLOC_BU_CD, STDERR_FILENO, FREE_NEW_ENV);
			new_len = ft_strlen(home) + ft_strlen(cmd[1]);
			ft_strlcpy(new_path, home, ft_strlen(home) + 1);
			ft_strlcat(new_path, cmd[1] + 1, new_len);
			if (chdir(new_path) == -1)
				ft_error(data, ERR_CD_ARG, STDERR_FILENO, CD_ARG);	
			free(new_path);
			get_abs_path(data, env_list);
			free_regular(data);
		}
}

/*
@glance			cd - and cd ~ case, change dir, update env OLDPWD and PWD
@pwd_flag		'cd -' has a behaviour to stdout the env PWD.
@return			this treniantion of the prject path is needed to handle tilde
				since tilde uses a new memory block that needs seperate freeing
				appart from env_list freeing.
*/

void	cd_builtin(t_data *data, char **cmd, t_env *env_list)
{
	if (!cmd[1] || !is_token_path(cmd[1]))
		cd_also_path(data, cmd, env_list);	
	else if (cmd[1][0] == '-')
	{
		data->pwd_flag = 1;
		data->new_path = our_get_env(env_list, "OLDPWD");
	}
	else if (cmd[1][0] == '-' || cmd[1][0] == '~' || cmd[2])
	{
		if (cmd[1][0] == '~')
			expand_tilde(data, cmd, env_list);
		else if (cmd[2])
			ft_error(data, ERR_CD_MAX, STDERR_FILENO, CD_ARG);
	return ;
	}
	else
		data->new_path = cmd[1];
	if (chdir(data->new_path) == -1)
	{
		ft_error(data, ERR_CD_ARG, STDERR_FILENO, CD_ARG);	
		return ;
	}
	get_abs_path(data, env_list);
	free_regular(data);
}
