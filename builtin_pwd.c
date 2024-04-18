/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 07:38:24 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/18 09:36:54 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		loop env list nodes and write when match
*/

void	pwd_builtin(t_data *data, t_env *env_list, int cd_calling)
{
	t_env	*temp;
	int	status;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, "PWD", ft_strlen(temp->key)))
		{
			if (ft_putstr_fd(temp->value, 1) < 0)
				ft_error(data);//TODO message write failed
			if (ft_putchar_fd('\n', 1) < 0)
				ft_error(data);//TODO message write failed
		}
		temp = temp->next;
	}
	if (cd_calling != 1)
		exit(status);
}

/*
@glance		//print env list to stdout, key=value\n
 *
 * */

void	env_builtin(t_data *data, t_env *env_list)
{
	t_env	*temp;
	int	status;
	temp = env_list;

	while (temp)
	{
		if (ft_putstr_fd(temp->key, 1) < 0)
			ft_error(data);//TODO msg write failed
		if (ft_putchar_fd('=', 1) < 0)
			ft_error(data);//TODO msg write failed
		if (ft_putstr_fd(temp->value, 1) < 0)
			ft_error(data);//TODO msg write failed
		if (ft_putchar_fd('\n', 1) < 0)
			ft_error(data);//TODO msg write failed
		temp = temp->next;
	}
	exit(status);
}
