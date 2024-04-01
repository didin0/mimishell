/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:08:42 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/01 22:03:23 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		loop the string array for - followed by one or more concecutve
			n-s.
@while		write out the string array cmd, skip option -n in case existing
*/

static	void	echo_stdout(t_data *data, char **cmd, int linebreak)
{
	int j;
	int option_flag;

	option_flag = 0;
	j = 1;
	while (cmd[j])
	{
		if (linebreak == 0 && option_flag == 0)
			j = 2;
		write(1, cmd[j], ft_strlen(cmd[j]));//TODO write fails, or use ft_puffd
		j++;
		if (cmd[j])	
			write(STDOUT_FILENO, " ", 1);
		option_flag = 1;
	}
	if (linebreak == 1)
		write(STDOUT_FILENO, "\n", 1);
	exit(EXIT_SUCCESS);
}

/*
@glance			check if in the string arrray cmd the second pos is the 
				option -n
				also that it is followed only by n characters.
@make_redir		the builtin can be followed on prompt line by any token
				so call recirections to be done by dup2().
@echo_stdout	write out the string array cmd
*/

static	void	echo_builtin(t_data *data, char **cmd)
{
	int j;
	int	linebreak;
	t_lexer *cur_node;

	linebreak = 1;
	j = 1;
	while (cmd[1][0] == '-' && cmd[1][j] == 'n')
		j++;
	if (!cmd[1][j])
		linebreak = 0;
	cur_node = keep_cur_node(data->lexer_list, ASK);
	if (is_token(cur_node->word, 0))
		make_redirections(data, cur_node);
	echo_stdout(data, cmd, linebreak);
}

/*
 @dev		there might be a better way to do this ft_strncmp only once
 			and have all builtins as seperate token types in one group
@glance		check string array cmd and call for a builtin function
*/

static int	exec_buitin_add(t_data *data, char **cmd, t_env *env_list, char **envp)
{
	if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
	{
		export_builtin(data, cmd,  env_list, envp);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
	{
		unset_builtin(data, cmd,  env_list, envp);
		return (0);
	}
	return (1);
}

int	exec_builtin(t_data *data, char **cmd, t_env *env_list, char **envp)
{
	if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
	{
		echo_builtin(data, cmd);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
	{
		pwd_builtin(data, env_list);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
	{
		env_builtin(data, env_list);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
		cd_builtin(data, cmd,  env_list);
		return (0);
	}
	if (!exec_buitin_add(data, cmd, env_list, envp))
		return (0);
	return (1);
}
