/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:55:13 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/25 18:09:40 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_also_path(t_data *data, char **cmd, t_env *env_list)
{
	char	*home;

	home = our_get_env(env_list, "HOME");
	if (!home)
		adv_error(data, ERR_CD_HOME, STDERR_FILENO, NO_EXIT);
	if (!cmd[1])
		data->new_path = home;
	else if (!is_token_path(cmd[1]))
		data->new_path = cmd[1];
}
