/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:11:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/11 15:23:50 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance 	look at one token, is it a command found in $PATH.
@temp_cmd	a forced solution to use existing func of find_good_path()
 * */

int	is_cmd(t_lexer *token, t_env *env_list)
{
	char **paths;
	char **temp_cmd;

	temp_cmd = (char **)malloc(sizeof(char **) + 1);
	paths = get_paths(env_list);
	temp_cmd[0] = token->word;
	if (find_good_path(temp_cmd, paths))
		return (0);
	return (1);
}
