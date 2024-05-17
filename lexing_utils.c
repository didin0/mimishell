/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:11:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/05 21:43:33 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance 	needed to figure out token_type.
			look at one token, is it a command found in $PATH.
@temp_cmd	a forced solution to use existing func of find_good_path()
 * */

int	is_cmd(t_data *data, t_lexer *token, t_env *env_list)
{
	
	get_paths(data, env_list);
	if (find_good_path(data, token->word))//TODO 
		return (0);
	return (1);
}

void	build_builtin_names(t_data *data)
{
	int i;
	
	data->builtin_names = ft_calloc(8, sizeof(char *));
	if (!data->builtin_names)
		ft_error(data, ERR_MALLOC_NAMES, STDERR_FILENO, FREE_NAMES);
	data->builtin_names[0] = ft_strdup("echo");
	data->builtin_names[1] = ft_strdup("cd");
	data->builtin_names[2] = ft_strdup("pwd");
	data->builtin_names[3] = ft_strdup("export");
	data->builtin_names[4] = ft_strdup("unset");
	data->builtin_names[5] = ft_strdup("env");
	data->builtin_names[6] = ft_strdup("exit");
	data->builtin_names[7] = NULL;
	i = 0;
	while (i < 7)
	{
		if (!data->builtin_names[i])		
			ft_error(data, ERR_MALLOC_NAMES, STDERR_FILENO, FREE_NAMES_A);
		i++;
	}
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
