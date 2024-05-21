/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:08:07 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/21 14:32:46 by rsainas          ###   ########.fr       */
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

	str = ft_split(env_var, '=');
	if (!str)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO ft_split malloc failure
	if (str[0])
	{
		new_node = create_env_node(data, str[0], str[1]);
		add_to_end(head, new_node);
	}
	free_array(str);
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
			new_value = ft_strdup(new_env[1]);
			if (!new_value)
				ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//				ft_error(data);//TODO ft_dup malloc failure
			free(temp->value);
			temp->value = new_value;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static void	check_args(t_data *data, char **cmd, t_env *env_list)
{
	if (!cmd[1])
		env_builtin(data, env_list);
//	else if (!cmd[2])
//		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO free, msg too many arguments
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
	char	**new_env;

	new_env = NULL;
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
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO "export: CMD[i]: not a valid identifier"
		new_env = ft_split(cmd[i], '=');//TODO ft_calloc fail
		if (!is_key_in_env(data, new_env, env_list))
			split_inc_term(data, cmd[i], &env_list);
		i++;
	}
	if (new_env)
		free_array(new_env);
	free(data->pids);
	free_lexer_list(data);
	free_3D_array(data->cmd);
}
