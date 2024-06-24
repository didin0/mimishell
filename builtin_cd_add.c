/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:55:13 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/24 16:15:02 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_also_path(t_data *data, char **cmd, t_env *env_list)
{
	char	*home;

	home = our_get_env(env_list, "HOME");
	if (!home)
	{
		printf("%s\n", home);
		adv_error(data, ERR_CD_HOME, STDERR_FILENO, FREE_M);
	}
	if (!cmd[1])
		data->new_path = home;
	else if (!is_token_path(cmd[1]))
		data->new_path = cmd[1];
}
