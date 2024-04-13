/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/13 17:18:04 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	ft_error(t_data *data)
{
	printf("substr or ft_calloc malloc failed\n");
//	free list TODO
	exit(EXIT_FAILURE);
}

/*
@glance		child process writes only to STDOUT	
@caution	if the error message gets written 2 times seamingly to stdout
			then run the ./minishell 2>err.log
			effectivlely sending the stderr stream to a log file.
			could be becuase we are running a shell with a shell.
*/

void	ft_error_errno(t_data *data, char *cmd)
{

	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(EXIT_FAILURE);//TODO free data
}

/*
 * does the string array contain exit token, what are the following arguments
 *
 * */

void	shell_exit(t_data *data)
{
	if (data->cmd[0])
	{
		if (data->cmd[1])
		{
			if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0]))
				&& !data->cmd[2])
				exit(data->exit_status);
		}
		if (!ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0]))
				&& !data->cmd[1])
				exit(data->exit_status);
	}
	if (!ft_strncmp(data->lexer_list->word, "$?",
		ft_strlen(data->lexer_list->word)) && !data->lexer_list->next)
				expand_status(data);
}
