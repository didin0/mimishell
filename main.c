/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/29 11:58:25 by mabbadi          ###   ########.fr       */
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

int	main(void)
{
	t_data	data;
	t_lexer	*lexer_list;

	while (1)
	{
		data.line = readline("minishell :"); // readline return a malloc char *
		add_history(data.line);	// add_history create and implement an history of commands working with directional key
		lexing(&data);
		show_list(data.lexer_list);
	}
	return (0);
}
