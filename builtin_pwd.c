/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 07:38:24 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/26 10:27:38 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		loop env list nodes and write when match
 * */


void	pwd_builtin(t_data *data, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, "PWD", ft_strlen(temp->key)))
		{
			write(1, temp->value, ft_strlen(temp->value));
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

/*
@glance		//print env list to stdout, key=value\n
 *
 * */

void	env_builtin(t_data *data, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		write(1, temp->key, ft_strlen(temp->key));
			write(1, "=", 1);
		write(1, temp->value, ft_strlen(temp->value));
			write(1, "\n", 1);
		temp = temp->next;
	}
}
