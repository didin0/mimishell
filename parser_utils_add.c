/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:33:40 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/26 19:34:48 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	store_remaining(t_data *data, char *str, t_env *env_list)
{
	data->remaining = ft_strdup(str + ft_strlen(env_list->key));
	if (!data->remaining)
		adv_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_M);
	re_bin(data->remaining, 0);
	data->result = malloc(ft_strlen(env_list->value)
			+ ft_strlen(data->remaining) + 1);
	if (!data->result)
		adv_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_M);
	re_bin(data->result, 0);
}

static void	string_composer(t_data *data, char *str, t_env *env_list)
{
	store_remaining(data, str, env_list);
	ft_strlcpy(data->result, env_list->value,
		ft_strlen(env_list->value) + 1);
	ft_strlcat(data->result, data->remaining,
		ft_strlen(data->result) + ft_strlen(data->remaining)
		+ 1);
}

static char	*is_expansion_sign_first(t_data *data)
{
	data->result = ft_itoa(data->exit_status);
	if (!data->result)
		adv_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_M);
	return (data->result);
}

/*
Performs variable expansion in a string based on the environment list
*/

char	*expen(t_data *data, char *str, t_env *env_list)
{
	int		size;
	char	*temp;

	if (ft_strlen(str) > 1)
		str++;
	size = key_size(str);
	if (str[0] == '?')
		return (is_expansion_sign_first(data));
	else
	{
		while (env_list)
		{
			if (!ft_strncmp(str, env_list->key, size)
				&& !ft_strncmp(str, env_list->key, ft_strlen(env_list->key)))
			{
				string_composer(data, str, env_list);
				return (data->result);
			}
			env_list = env_list->next;
		}
	}
	temp = re_bin(ft_strdup(str), 0);
	return (ft_strremove(data, temp, 0, size));
}
