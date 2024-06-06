/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:36:21 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 12:40:46 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_regular(t_data *data)
{	
	free(data->pids);
	free_lexer_list(data);
	free_3D_array(data->cmd);
}

static void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

//delete a singly linked list entry
static void	ft_lstdelone1(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

//create a singly linked list entry at the end
static void	*ft_lstadd_back1(t_list **lst, t_list *new)
{
	t_list	*t;

	if (*lst)
	{
		t = ft_lstlast(*lst);
		t->next = &*new;
	}
	else
		*lst = new;
	return (new->content);
}

//create a singly linked list
static t_list	*ft_lstnew1(void *content)
{
	t_list	*rtn;

	rtn = (t_list *)malloc(sizeof(t_list));
	if (!rtn)
		return (rtn = 0);
	rtn->next = 0;
	rtn->content = content;
	return (rtn);
}

//perform a delete function on each entry in a singly linked list
static void	ft_lstclear1(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone1(*lst, del);
		*lst = tmp;
	}
}

/*
@glance		list to keep pointers that have to be cleaned at exit or prompt return
			ie command tripple array cmd.
*/

void	*re_bin(void *ptr, bool clean)
{
	static t_list	*garbage;

	if (clean)
		return (ft_lstclear1(&garbage, free_ptr), NULL);
	else
		return (ft_lstadd_back1(&garbage, ft_lstnew1(ptr)), ptr);
}

/*
@glance		list to keep pointers that have to accessible while prompt return
			ie environmental variables env_list.
*/

void	*re_bin_prompt(void *ptr, bool clean)
{
	static t_list	*prompt;

	if (clean)
		return (ft_lstclear1(&prompt, free_ptr), NULL);
	else
		return (ft_lstadd_back1(&prompt, ft_lstnew1(ptr)), ptr);
}
