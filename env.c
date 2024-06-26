/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:00:26 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/06 22:49:59 by rsainas          ###   ########.fr       */
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
		adv_error(data, ERR_MALLOC_ENV, STDERR_FILENO, FREE_ENV);
	re_bin_prompt(new_env, 0);
	new_env->key = re_bin_prompt(ft_strdup(key), 0);
	new_env->value = re_bin_prompt(ft_strdup(value), 0);
	if (!new_env->key || !new_env->value)
	{
		if (ft_putstr_fd(ERR_MALLOC_ENV, 1) < 0)
			adv_error(data, ERR_WRITE_FAIL, STDOUT_FILENO, FREE_ENV);
	}
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

static void	split_and_add(t_data *data, char *env_var)
{
	char	**str;
	t_env	*new_node;

	str = ft_adv_split(env_var, '=');
	if (!str)
		adv_error(data, ERR_MALLOC_ENV, STDERR_FILENO, FREE_M);
	if (str[0] && str[1])
	{
		new_node = create_env_node(data, str[0], str[1]);
		add_to_end(&data->env_list, new_node);
	}
}

t_env	*get_env_to_list(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		split_and_add(data, envp[i]);
		i++;
	}
	return (data->env_list);
}
