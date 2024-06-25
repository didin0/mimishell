/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/06 23:49:08 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	adv_error(t_data *data, const char *msg, int fd, int flag)
{
	(void)data;
	if (flag != EXIT_NO_ERROR && flag != NO_EXIT_NO_MSG)
		ft_putstr_fd("Error: ", fd);
	ft_putstr_fd((char *)msg, fd);
	re_bin(NULL, 1);
	if (flag == EXIT_NO_ERROR || flag == FREE_M)
		re_bin_prompt(NULL, 1);
	if (flag == EXIT_NO_ERROR)
		exit(data->exit_status);
	if (flag == FREE_ENV || flag == FREE_FORK || flag == EXIT
		|| flag == FREE_M)
		exit(EXIT_FAILURE);
}

/*
@glance		child process writes only to STDOUT	
@caution	if the error message gets written 2 times seamingly to stdout
			then run the ./minishell 2>err.log
			effectivlely sending the stderr stream to a log file.
			could be becuase we are running a shell with a shell.
*/

void	ft_error_errno(char **cmd)
{
	ft_putstr_fd(*cmd, STDOUT_FILENO);
	ft_putstr_fd(": command not found\n", STDOUT_FILENO);
	re_bin(NULL, 1);
	exit(EXIT_FAILURE);
}
