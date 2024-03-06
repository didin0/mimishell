/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:00:26 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/06 11:20:52 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	return (new_env);
}

void	add_to_end(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	split_and_add(char *env_var, t_env **head)
{
	char	**str;
	t_env	*new_node;

	str = ft_split(env_var, '=');
	if (str[0] && str[1])
	{
		new_node = create_env_node(str[0], str[1]);
		add_to_end(head, new_node);
	}
}

t_env	*get_env_to_list(char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		split_and_add(envp[i], &env_list);
		i++;
	}
	return (env_list);
}
