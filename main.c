/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/28 18:02:16 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;

	while (1)
	{
		i = 0;
		data.line = readline("minishell :");
		add_history(data.line);
		lexing(&data);
		show_list(data.lexer_list);
	}
	return (0);
}
