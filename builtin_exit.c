/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:22:37 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 13:06:17 by rsainas          ###   ########.fr       */
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
		adv_error(data, ERR_EXIT_MAX, STDERR_FILENO, EXIT_NO_ERROR);
	if (cmd[1])
	{
		if (ft_isdigit_sign(cmd[1]) == 0)
			adv_error(data, ERR_EXIT_ARG, STDERR_FILENO, EXIT_NO_ERROR);
		data->exit_status = ft_atoi(cmd[1]) % 256;
	}
	adv_error(data, ERR_EXIT, STDOUT_FILENO, EXIT_NO_ERROR);
}
