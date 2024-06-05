/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:53 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/05 22:28:38 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		Add a node to the end of the linked list type 't_lexer'
*/

void	ft_lstlex_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (new == NULL)
		return ;
	if ((*lst)->word == NULL)
	{
//		free(*lst);
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
@glance		Create a new node
*/

t_lexer	*ft_lstlex_new(t_data *data, void *word)
{
	t_lexer *result;

	result = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (!result)	
		ft_error(data, ERR_MALLOC_LI, STDERR_FILENO, FREE_BUFF);
	re_bin(result, 0);
	result->word = word;
	result->type = -1;
	result->next = NULL;
	return (result);
}
