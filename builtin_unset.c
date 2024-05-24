/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:05:36 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/24 19:11:31 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@if&else		if a middle node, else untie an end node from env_list.
*/

static void	untie_mid_node(t_env *node, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (temp->next == node)
		{
			free(node->key);
			free(node->value);
			if (node->next)
				temp->next = node->next;
			else
				temp->next = NULL;
			free(node);
			break ;
		}
		temp = temp->next;
	}
}

/*
@glance			find the env in list
@1st if			untie the node from the middle of the list
@2nd if			untie the node from the end of the list
*/

static void	is_key_in_env(char *del_env, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!adv_strncmp(temp->key, del_env))
		{
			untie_mid_node(temp, env_list);
			break ;
		}
		temp = temp->next;
	}
}

void	unset_builtin(t_data *data, char **cmd, t_env *env_list)
{
	int	i;

	if (!adv_strncmp(cmd[0], "export"))
	{
		export_builtin(data, cmd, env_list);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		is_key_in_env(cmd[i], env_list);
		i++;
	}
	free_regular(data);
}
