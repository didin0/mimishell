/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:08:07 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/17 22:17:06 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance 	splits a string by = sign
			this is a similar function to env.c thus a= is also an env.
*/

static	void	split_inc_term(char *env_var, t_env **head)
{
	char	**str;
	t_env	*new_node;

	str = ft_split(env_var, '=');//TOOD ft_split calloc failure
	if (str[0])
	{
		new_node = create_env_node(str[0], str[1]);
		add_to_end(head, new_node);
	}
	free(str);
}

/*
@glance		for comparisison comapre ft_strcmp with both lengths
*/

static	int	is_key_in_env(char **new_env, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, new_env[0], ft_strlen(new_env[0]))
		&& !ft_strncmp(temp->key, new_env[0], ft_strlen(temp->key)))
		{	
			temp->value = ft_strdup(new_env[1]);
			return (1);
		}
		temp = temp->next;
	}
	if (!ft_strncmp(temp->key, new_env[0], ft_strlen(new_env[0])))
	{
		temp->value = ft_strdup(new_env[1]);
		return (1);
	}
	return (0);
}

/*
@glance			main while looks at each string in array.
				inner while checkes if variable mathces a standardad.
@3rd if			variable key match found, update value,
				if not found then append to env_list.
*/

void	export_builtin(t_data *data, char **cmd, t_env *env_list)
{
	int	i;
	int j;
	char **new_env;

	if (!cmd[1])
		ft_error(data);//TODO message declare builtin not implemented, use env
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i])
		{
			if (!ft_isalnum(cmd[i][j]) || cmd[i][j] == ' ')
				break;
			j++;
		}
		if (cmd[i][j] != '=')
			ft_error(data);//TODO "export: CMD[i]: not a valid identifier"
		new_env = ft_split(cmd[i], '=');//TODO ft_calloc fail
		if (!is_key_in_env(new_env, env_list))	
			split_inc_term(cmd[i], &env_list);
		i++;
	}
	free(new_env);
}
