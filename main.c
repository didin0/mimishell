/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/25 15:32:41 by mabbadi          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_lexer	*lexer_list;
	t_env	*env_list = get_env_to_list(envp);

	while (1)
	{
		data.line = readline("\033[36mminishell :\033[m "); // readline return a malloc char *
		add_history(data.line);
		lexing(&data);
		token_type(&data, env_list);
		parsing(&data, env_list);
//		// show_list(data.lexer_list);
		execution(&data, env_list);
	}
	return (0);
}
