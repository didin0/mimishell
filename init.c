/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:01:57 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/28 17:02:20 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, t_lexer *lexer_list)
{
	data->line = malloc(sizeof(char *) + 1);
	lexer_list = ft_calloc(sizeof(t_lexer), 1);
	lexer_list->next = NULL;
	data->lexer_list = lexer_list;
}
