/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:08:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/28 13:55:15 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		loop the string array for - followed by one or more concecutive
			n-s.
@while		write out the string array cmd, skip option -n in case existing
*/

static void	echo_stdout(t_data *data, char **cmd, int line_break)
{
	int	option_flag;
	int	j;

	if (line_break == 0)
		j = 2;
	else
		j = 1;
	option_flag = 0;
	while (cmd[j])
	{
		if (ft_putstr_fd(cmd[j], 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		if (cmd[j + 1] && ft_putchar_fd(' ', 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
		j++;
		option_flag = 1;
	}
	if (line_break == 1)
	{
		if (ft_putchar_fd('\n', 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
	}
}

/*
@glance			check if in the string arrray cmd the second pos is the
				option -n
@while and if	-n option is the first argument, check the last char
				of the first argument strng.
				also that it is followed only by n characters.
@echo_stdout	write out the string array cmd
*/

static void	echo_builtin(t_data *data, char **cmd)
{
	int	j;
	int	line_break;

	j = 1;
	line_break = 1;
	if (cmd[1] && cmd[1][0] == '-')
	{
		while (cmd[1][j] == 'n')
			j++;
		if (cmd[1][j] == '\0')
			line_break = 0;
	}
	echo_stdout(data, cmd, line_break);
	re_bin(NULL, 1);
}

/*
@glance		check string array cmd and call for a builtin function
*/

int	exec_builtin_parent(t_data *data, char **cmd, t_env *env_list)
{
	if (!adv_strncmp(cmd[0], "export") || !adv_strncmp(cmd[0], "unset"))
	{
		unset_builtin(data, cmd, env_list);
		return (0);
	}
	if (!adv_strncmp(cmd[0], "cd"))
	{
		cd_builtin(data, cmd, env_list);
		return (0);
	}
	else if (!adv_strncmp(cmd[0], "exit"))
	{
		exit_builtin(data, cmd);
		return (0);
	}
	return (1);
}

int	exec_builtin_child(t_data *data, char **cmd, t_env *env_list)
{
	if (!adv_strncmp(cmd[0], "echo"))
	{
		echo_builtin(data, cmd);
		return (0);
	}
	if (!adv_strncmp(cmd[0], "pwd"))
	{
		pwd_builtin(data);
		re_bin(NULL, 1);
		return (0);
	}
	if (!adv_strncmp(cmd[0], "env"))
	{
		env_builtin(data, env_list);
		re_bin(NULL, 1);
		return (0);
	}
	return (1);
}
