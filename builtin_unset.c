/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:05:36 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/21 14:55:38 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	untie_mid_node(t_env *node, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (temp->next == node)
		{
			temp->next = node->next;
			break ;
		}
		temp = temp->next;
	}
	free(node);
}

static void	untie_last_node(t_env *node, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (temp->next == node)
		{
			temp->next = NULL;
			break ;
		}
		temp = temp->next;
	}
	free(node);
}

/*
@glance			find the env in list
@1st if			untie the node from the middle of the list
@2nd if			untie the node from the end of the list
 *
 * */

static void	is_key_in_env(char *del_env, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, del_env, ft_strlen(del_env))
			&& !ft_strncmp(temp->key, del_env, ft_strlen(temp->key)))
			untie_mid_node(temp, env_list);
		temp = temp->next;
	}
	if (!ft_strncmp(temp->key, del_env, ft_strlen(del_env)))
		untie_last_node(temp, env_list);
}

void	unset_builtin(t_data *data, char **cmd, t_env *env_list)
{
	int	i;

	if (!adv_strncmp(cmd[0], "export"))
	{
		export_builtin(data, cmd, env_list);
		return ;
	}
//	if (!cmd[1])
//		ft_error(data, ERR_UNSET, STDERR_FILENO, NO_STDOUT);
	i = 1;
	while (cmd[i])
	{
		is_key_in_env(cmd[i], env_list);
		i++;
	}
	free(data->pids);
	free_lexer_list(data);
	free_3D_array(data->cmd);
}
