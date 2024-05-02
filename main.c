/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/02 12:38:14 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Debugging function to print a list
void	show_list(t_lexer *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("list [%d] type (%d) ft_strlen(list->word) %zu :%s\n", i, list->type, ft_strlen(list->word), list->word);
		list = list->next;
		i++;
	}
}

void	show_env_list(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("key [%s] value (%s)\n", list->key, list->value);
		list = list->next;
		i++;
	}
}

void	show_cmd(char ***cmd, t_data *data)
{
	int i;
	int j;
	int	cmd_count;

	cmd_count = count_token_type(data, BUILTIN, COMMAND);
	i = 0;
	while (i < cmd_count)
	{
		j = 0;
		while (cmd[i][j])
		{
			printf("cmd [%d] [%d] %s\n", i, j, cmd[i][j]);
			j++;
		}
		i++;
	}
}


/*
@if		handle ctrl-D EOF (signal/char) in shell interactive mode with exit message
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lexer	*lexer_list;
	t_env	*env_list = get_env_to_list(envp);

	init_data(&data);
	while (1)
	{
		init_signals(&data);
		data.line = readline("\033[36mminishell :\033[m "); // readline return a malloc char *
		if (!data.line)
		{
			if (ft_putstr_fd("exit\n", 1) < -1)
				ft_error(&data);	
			break;
		}
		if (!ft_strncmp(data.line, "", ft_strlen(data.line)))
		{
//			ft_free some sort TODO
			continue;
		}	
		add_history(data.line);
		lexing(&data);
		token_type(&data, env_list);
//		parsing(&data, env_list);
//		show_list(data.lexer_list);
		execution(&data, env_list);
//		shell_exit(&data);
	}
	free(data.line);
	return (0);
}
