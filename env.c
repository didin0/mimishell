/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:00:26 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/03 16:13:53 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		ft_strdup here assures the env valiables are put on heap.
			This helps to maintain stability and predictability of the program.
*/

t_env	*create_env_node(t_data *data, char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (!new_env->key || !new_env->value)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);//seperate check needed
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

static void	split_and_add(t_data *data, char *env_var, t_env **head)
{
	char	**str;
	t_env	*new_node;

	str = ft_split(env_var, '=');
	if (!str)	
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);//TODO
	if (str[0] && str[1])
	{
		new_node = create_env_node(data, str[0], str[1]);
		add_to_end(head, new_node);
	}
	free_array(str);
}

t_env	*get_env_to_list(t_data *data, char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		split_and_add(data, envp[i], &env_list);
		i++;
	}
	data->env_list = env_list;
	return (env_list);
}
