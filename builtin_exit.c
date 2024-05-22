/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:22:37 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/22 12:24:39 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_sign(char *str)
{
	while (str && ((*str >= 48 && *str <= 57) || *str == 43 || *str == 45))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

/*
@glance			deal exit builtin in child process
@isdigit_sign	check for numbers and single signs prior atoi
@modulo 		mimic bash int truncation to 8 bits -255 to 255, else overflow
*/

void	exit_builtin(t_data *data, char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		if (ft_putstr_fd("exit: too many arguments\n", 1) < 0)
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO msg write failed
		exit(EXIT_FAILURE);
	}
	if (ft_putstr_fd("exit\n", 1) < 0)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO msg write failed
	if (cmd[1])
	{
		if (ft_isdigit_sign(cmd[1]) == 0)
		{
			if (ft_putstr_fd("exit: numeric argument required\n", 1) < 0)
				ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//				ft_error(data);//TODO msg write failed
			else
				exit(EXIT_FAILURE);//TODO msg write failed
		}
		data->exit_status = ft_atoi(cmd[1]) % 256;
	}
	free_env_list(data->env_list);	
	free_regular(data);
	exit(data->exit_status);
}
