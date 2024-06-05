/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:08:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/05 15:45:07 by rsainas          ###   ########.fr       */
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
	int	j;
	int	option_flag;

	option_flag = 0;
	j = 1;
	while (cmd[j])
	{
		if (line_break == 0 && option_flag == 0)
			j = 2;
		if (ft_putstr_fd(cmd[j], 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, FREE_W_BU);
		j++;
		if (cmd[j])
		{
			if (ft_putchar_fd(' ', 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, FREE_W_BU);
		}
		option_flag = 1;
	}
	if (line_break == 1)
	{
		if (ft_putchar_fd('\n', 1) < 0)
			ft_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, FREE_W_BU);
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
	int		j;
	int		line_break;

	line_break = 1;
	j = 1;
	if (cmd[1] && cmd[1][0] == '-')
	{
		while (cmd[1][j] == 'n')
			j++;
	}
	if (cmd[1] && (cmd[1][0] == '-' && cmd[1][j] == '\0'))
		line_break = 0;
	echo_stdout(data, cmd, line_break);
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
		pwd_builtin(data, env_list);
		return (0);
	}
	if (!adv_strncmp(cmd[0], "env"))
	{
		env_builtin(data, env_list);
		return (0);
	}
	return (1);
}
