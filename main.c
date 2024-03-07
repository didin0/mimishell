/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/07 12:35:30 by mabbadi          ###   ########.fr       */
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
		printf("list [%d] : %s\n", i, list->word);
		list = list->next;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lexer	*lexer_list;
	t_env	*env_list = get_env_to_list(envp);

	while (1)
	{
		data.line = readline("minishell :"); // readline return a malloc char *
		add_history(data.line);	// add_history create and implement an history of commands working with directional key
		lexing(&data);
		// show_list(data.lexer_list);
		execution(&data, env_list);
	}
	return (0);
}
