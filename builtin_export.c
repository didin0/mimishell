/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:08:07 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 20:09:34 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance 	splits a string by = sign
			this is a similar function to env.c thus a= is also an env.
*/

static void	split_inc_term(t_data *data, char *env_var, t_env **head)
{
	char	**str;
	t_env	*new_node;

	new_node = NULL;
	str = ft_split(env_var, '=');
	if (!str)
		adv_error(data, ERR_MALLOC_BU_EX, STDERR_FILENO, FREE_M);	
	re_bin_prompt(str, 0);
	if (str[0])
	{
		new_node = create_env_node(data, str[0], str[1]);
		add_to_end(head, new_node);
	}
}

/*
@glance		for comparisison comapre ft_strcmp with both lengths
*/

static int	is_key_in_env(t_data *data, char **new_env, t_env *env_list)
{
	t_env	*temp;
	char	*new_value;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, new_env[0], ft_strlen(new_env[0]))
			&& !ft_strncmp(temp->key, new_env[0], ft_strlen(temp->key)))
		{
			new_value = re_bin_prompt(ft_strdup(new_env[1]), 0);
			if (!new_value)
				adv_error(data, ERR_MALLOC_BU_EX, STDERR_FILENO, FREE_M);	
			temp->value = new_value;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

/*
@2nd if		minimum needed for an env is a letter followed by = sign
			start looking from the secound char and return
*/

static void	check_args(t_data *data, char **cmd, t_env *env_list)
{

	if (!cmd[1])
		env_builtin(data, env_list);
}

/*
@glance			main while looks at each string in array.
				inner while checkes if variable mathces a standardad.
@3rd if			variable key match found, update value,
				if not found then append to env_list.
*/

void	export_builtin(t_data *data, char **cmd, t_env *env_list)
{
	int		i;
	int		j;

	check_args(data, cmd, env_list);
	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i])
		{
			if (!ft_isalnum(cmd[i][j]) || cmd[i][j] == ' ')
				break ;
			j++;
		}
		if (cmd[i][j] != '=')
			return (adv_error(data, ERR_EX_ARG, STDOUT_FILENO, NO_EXIT));	
		data->new_env = re_bin_prompt(ft_split(cmd[i], '='), 0);
		if (!data->new_env)	
			adv_error(data, ERR_MALLOC_BU_EX, STDERR_FILENO, FREE_M);	
		if (!is_key_in_env(data, data->new_env, env_list))
			split_inc_term(data, cmd[i], &env_list);
		i++;
	}
}
