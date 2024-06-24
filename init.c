/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:01:57 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/21 18:35:30 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->env_list = NULL;
	data->exit_status = 0;
	data->pwd_flag = 0;
	data->new_path = NULL;
	data->result = NULL;
	data->remaining = NULL;
	data->new_str = NULL;
	data->new_env = NULL;
}
