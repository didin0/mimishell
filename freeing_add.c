/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:36:21 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/24 14:28:15 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_regular(t_data *data)
{
	free(data->pids);
	free_lexer_list(data);
	free_3d_array(data->cmd);
}

static void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/*
@glance		delete a list node
*/

static void	ft_lstdelone_bin(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*
@glance		append a node to the end of the list
*/

static void	*ft_lstadd_back_bin(t_list **lst, t_list *new)
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

/*
@glance		create a list
*/

static t_list	*ft_lstnew_bin(void *content)
{
	t_list	*rtn;

	rtn = (t_list *)malloc(sizeof(t_list));
	if (!rtn)
		return (rtn = 0);
	rtn->next = 0;
	rtn->content = content;
	return (rtn);
}

/*
@glance		free a singly linked list
*/

static void	ft_lstclear_bin(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_bin(*lst, del);
		*lst = tmp;
	}
}
/*
@glance		list to keep pointers that have to accessible while prompt return
			ie environmental variables env_list.
*/

void	*re_bin_prompt(void *ptr, bool clean)
{
	static t_list	*prompt;

	if (clean)
		return (ft_lstclear_bin(&prompt, free_ptr), NULL);
	else
		return (ft_lstadd_back_bin(&prompt, ft_lstnew_bin(ptr)), ptr);
}

/*
@glance		list to keep pointers that have to be cleaned at exit or prompt return
			ie command tripple array cmd.
*/

void	*re_bin(void *ptr, bool clean)
{
	static t_list	*garbage;

	if (clean)
		return (ft_lstclear_bin(&garbage, free_ptr), NULL);
	else
		return (ft_lstadd_back_bin(&garbage, ft_lstnew_bin(ptr)), ptr);
}

