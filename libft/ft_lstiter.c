/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:51:38 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/13 16:34:31 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *), int type)
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		if (type == 0)
		{
			f((void *)(intptr_t)lst->index);
			lst = lst->next;
		}
		else if (type == 1)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
