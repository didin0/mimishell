/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 07:38:24 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/03 12:47:12 by rsainas          ###   ########.fr       */
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
				ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
			if (ft_putchar_fd('\n', 1) < 0)
				ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
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
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
		if (ft_putchar_fd('=', 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
		if (ft_putstr_fd(temp->value, 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
		if (ft_putchar_fd('\n', 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, STDOUT);
		temp = temp->next;
	}
}
