// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   freeing_add2.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/24 14:22:00 by mabbadi           #+#    #+#             */
// /*   Updated: 2024/06/24 14:22:14 by mabbadi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// /*
// @glance		child process writes only to STDOUT
// @caution	if the error message gets written 2 times seamingly to stdout
// 			then run the ./minishell 2>err.log
// 			effectivlely sending the stderr stream to a log file.
// 			could be becuase we are running a shell with a shell.
// */

// void	ft_error_errno(char **cmd)
// {
// 	ft_putstr_fd(*cmd, STDOUT_FILENO);
// 	ft_putstr_fd(": command not found\n", STDOUT_FILENO);
// 	re_bin(NULL, 1);
// 	exit(EXIT_FAILURE);
// }
