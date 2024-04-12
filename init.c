/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:01:57 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/12 18:09:37 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialize the structure to avoid segmentation fault
/*
void	init_data(t_data *data, t_lexer *lexer_list)
{
	data->line = malloc(sizeof(char *) + 1);
	lexer_list = ft_calloc(sizeof(t_lexer), 1);
	lexer_list->next = NULL;
	data->lexer_list = lexer_list;
	data->exit_flag = 0;
}
*/
void init_data(t_data *data)
{		
	add_history(data->line);
}
