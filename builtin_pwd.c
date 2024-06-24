/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 07:38:24 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/21 15:56:06 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		loop env list nodes and write when match
*/

void	pwd_builtin(t_data *data, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, "PWD", ft_strlen(temp->key)))
		{
			if (ft_putstr_fd(temp->value, 1) < 0)
				adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
			if (ft_putchar_fd('\n', 1) < 0)
				adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
			break ;
		}
		temp = temp->next;
	}
}

/*
@glance		print env list to stdout, key=value\n
*/

void	env_builtin(t_data *data, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_putstr_fd(temp->key, 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		if (ft_putchar_fd('=', 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		if (ft_putstr_fd(temp->value, 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		if (ft_putchar_fd('\n', 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		temp = temp->next;
	}
}
