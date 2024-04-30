/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:11:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/30 10:58:33 by rsainas          ###   ########.fr       */
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
	char	**paths;
	char	*temp_cmd;

	paths = get_paths(data, env_list);
	if (find_good_path(data, token->word, paths))
		return (0);
	return (1);
}

int	is_builtin(t_data *data, char *word)
{
	char	**builtin_names;
	int		i;

	builtin_names = (char **)malloc(sizeof(char *) * 8 + 1);
	if (!builtin_names)
		ft_error(data);//TODO
	builtin_names[0] = ft_strdup("echo");
	builtin_names[1] = ft_strdup("cd");
	builtin_names[2] = ft_strdup("pwd");
	builtin_names[3] = ft_strdup("export");
	builtin_names[4] = ft_strdup("unset");
	builtin_names[5] = ft_strdup("env");
	builtin_names[6] = ft_strdup("exit");
	builtin_names[7] = NULL;
	i = 0;
	while (i < 7)
	{
		if (!adv_strncmp(word, builtin_names[i]))
			return (1);
		i++;
	}
	free_array(builtin_names);
	return (0);
}
