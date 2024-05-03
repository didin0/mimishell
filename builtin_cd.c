/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:20:38 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/03 12:59:31 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*our_get_env(t_env *env_list, char *env)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, env, ft_strlen(env)))
			break ;
		temp = temp->next;
	}
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
				ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
		}
		temp = temp->next;
	}
}

static void	get_abs_path(t_data *data, t_env *env_list, int pwd_flag)
{
	char	abs_path[PATH_MAX];

	if (pwd_flag == 1)
		pwd_builtin(data, env_list);
	change_env(data, env_list, "OLDPWD", our_get_env(env_list, "PWD"));
	if (getcwd(abs_path, sizeof(abs_path)) != NULL)
		change_env(data, env_list, "PWD", abs_path);
	else
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO message cd: error retrieving currend directory
}

/*
@ft_strl		copy home path, concatenate cd first argument skipping tilde 
*/

static char	*expand_tilde(t_data *data, char **cmd, t_env *env_list)
{
	char	*new_path;
	char	*home;
	size_t	new_len;

	if (cmd[2])
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO message cd: too many arguments
	else if (cmd[1][0] == '~')
	{
		if (cmd[1][1] == '\0' || cmd[1][1] == '/'
				|| !ft_strncmp(cmd[1], "~/.", 3))
		{
			home = our_get_env(env_list, "HOME");
			new_path = malloc(ft_strlen(home) + ft_strlen(cmd[1]));
			if (!new_path)
				ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
			new_len = ft_strlen(home) + ft_strlen(cmd[1]);
			ft_strlcpy(new_path, home, ft_strlen(home) + 1);
			ft_strlcat(new_path, cmd[1] + 1, new_len);
			return (ft_strdup(new_path));
		}
	}
	return (cmd[1]);
}

/*
@glance			cd - and cd ~ case, change dir, update env OLDPWD and PWD
@pwd_flag		'cd -' has a behaviour to stdout the env PWD.
*/

void	cd_builtin(t_data *data, char **cmd, t_env *env_list)
{
	char	*new_path;
	char	*home;
	int		pwd_flag;

	new_path = NULL;
	pwd_flag = 0;
	home = our_get_env(env_list, "HOME");
	if (!home)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO
	if (!cmd[1])
		new_path = home;
	else if (cmd[1][0] == '-')
	{
		if (cmd[1][1] != '\0')
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO
		pwd_flag = 1;
		new_path = our_get_env(env_list, "OLDPWD");
	}
	else
		new_path = expand_tilde(data, cmd, env_list);
	if (chdir(new_path) == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO err STDERR "cd: $new_path no such file or dir"
	get_abs_path(data, env_list, pwd_flag);
	if (new_path)
		free(new_path);
}
