/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:02:09 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/04 14:20:46 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*categorize_tokens(t_data *data, t_lexer *temp, t_env *env_list)
{
	build_builtin_names(data);
	if (is_builtin(data, temp->word) == 1)
		temp->type = 0;
	else if (!is_cmd(data, temp, env_list))
		temp->type = 1;
	else if (temp->word[0] == '-')
		temp->type = 2;
	else if (ft_strrchr(temp->word, '"'))
		temp->type = 31;
	else if (temp->word[0] == '\'')
		temp->type = 32;
	else if (temp->word[0] == '<' && temp->word[1] == '<')
		temp->type = 400;
	else if (temp->word[0] == '>' && temp->word[1] == '>')
		temp->type = 411;
	else if (temp->word[0] == '<' && temp->word[1] == '\0')
		temp->type = 40;
	else if (temp->word[0] == '>' && temp->word[1] == '\0')
		temp->type = 41;
	else if (temp->word[0] == '|')
		temp->type = 5;
	return (temp);
	free_array(data->builtin_names);
}

void	token_type(t_data *data, t_env *env_list)
{
	t_lexer	*temp;
	int		fd;

	temp = data->lexer_list;
	fd = 0;
	while (temp)
	{
		temp = categorize_tokens(data, temp, env_list);
		if (temp->word[0] == '$')
		{
			if (temp->word[1] == '?')
				temp->type = 6;
			else
				temp->type = 7;
		}
		fd = open(temp->word, O_RDONLY);
		if (fd != -1)
		{
			temp->type = 10;
			close(fd);
		}
		else if (temp->type == -1)
			temp->type = 3;
		temp = temp->next;
	}
}

/*
@glance 	loop until the next pipe of redirection
			loop back until the closing quote
			return closing quote position.
*/

int	ft_strchr_end(char *s, char c, int i)
{
	while (is_token(s, i) == 0 && s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (0);
}

int	is_quote_closed(char *s, char c)
{
	int	count;

	count = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}
