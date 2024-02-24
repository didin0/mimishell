/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:53 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/22 16:04:46 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstlex_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lexer	*ft_lstlex_new(void *word)
{
	t_lexer	*result;

	result = (t_lexer *)ft_calloc(sizeof(t_list), 1);
	if (!result)
		return (NULL);
	result->word = word;
	result->next = NULL;
	return (result);
}