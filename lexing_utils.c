/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:11:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/06 16:24:40 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_array_allocated(t_data *data, char **arr, int len)
{	
	int	i;
	
	i = 0;
	while (i++ < len - 1)
	{
		if (!arr[i])
			adv_error(data, ERR_MALLOC_LU, STDERR_FILENO, FREE_M);
	}
}

/*
@glance	categorize abs path /bin/ls & this rel ./a.out  as a command
*/

int	is_token_path(char *cmd)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	if (cmd[i] == '/' || (cmd[i] == '.' && (cmd[j] == '.' || cmd[j] == '/')))
			return (0);
	return (1);
}

/*
@glance 	needed to figure out token_type.
			look at one token, is it a command found in $PATH.
@temp_cmd	a forced solution to use existing func of find_good_path()
*/

int	is_cmd(t_data *data, t_lexer *token, t_env *env_list)
{	
	get_paths(data, env_list);
	if (!is_token_path(token->word))
		return (0);
	if (find_good_path(data, token->word))
		return (0);
	return (1);
}

void	build_builtin_names(t_data *data)
{
	data->builtin_names = ft_calloc(8, sizeof(char *));
	if (!data->builtin_names)
		adv_error(data, ERR_MALLOC_LU, STDERR_FILENO, FREE_M);	
	re_bin(data->builtin_names, 0);
	data->builtin_names[0] = re_bin(ft_strdup("echo"), 0);
	data->builtin_names[1] = re_bin(ft_strdup("cd"), 0);
	data->builtin_names[2] = re_bin(ft_strdup("pwd"), 0);
	data->builtin_names[3] = re_bin(ft_strdup("export"), 0);
	data->builtin_names[4] = re_bin(ft_strdup("unset"), 0);
	data->builtin_names[5] = re_bin(ft_strdup("env"), 0);
	data->builtin_names[6] = re_bin(ft_strdup("exit"), 0);
	data->builtin_names[7] = NULL;
	is_array_allocated(data, data->builtin_names, 7);
}

int	is_builtin(t_data *data, char *word)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (!adv_strncmp(word, data->builtin_names[i]))
			return (1);
		i++;
	}
	return (0);
}
