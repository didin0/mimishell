/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:22:37 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/01 22:04:07 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_data *data, char  **cmd)
{
	int	status;

	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		return;
	status = 0;
	if (cmd[1])
		status = ft_atoi(cmd[1]);
	exit(status);
}
