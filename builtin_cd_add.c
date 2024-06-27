/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:58:09 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/27 19:38:49 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_also_path(t_data *data, char **cmd, t_env *env_list)
{
	char	*home;

	home = our_get_env(env_list, "HOME");
	if (!home)
		adv_error(data, ERR_CD_HOME, STDERR_FILENO, FREE_M);
	if (!cmd[1])
		data->new_path = home;
	else if (!is_token_path(cmd[1]))
		data->new_path = cmd[1];
}

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
