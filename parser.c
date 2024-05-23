/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:16:49 by abaccari          #+#    #+#             */
/*   Updated: 2024/05/23 21:07:16 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removes a substring from a string starting from a given position
char	*ft_strremove(char *s, int start, int n)
{
	int	len;
	int	i;

	len = 0;
	while (s[len])
		len++;
	if (start >= len)
		return (NULL);
	i = start;
	while (s[i + n] != '\0')
	{
		s[i] = s[i + n];
		i++;
	}
	s[i] = '\0';
	return (s);
}

// Determines the size of a key in a string (used in the expansion function)
int	key_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$' || str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

// Performs variable expansion in a string based on the environment list
char	*expen(t_data *data, char *str, t_env *env_list)
{
	int		size;

	if (ft_strlen(str) > 1)
		str++;
	size = key_size(str);
	while (env_list)
	{
		if (!ft_strncmp(str, env_list->key, size))
		{
			data->remaining = ft_strdup(str + ft_strlen(env_list->key));
			if (!data->remaining)
				ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PAR_RE);
			data->result = malloc(ft_strlen(env_list->value)
					+ ft_strlen(data->remaining) + 1);
			if (!data->result)
				ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PAR_RE);
			ft_strlcpy(data->result, env_list->value, ft_strlen(env_list->value)
					+ 1);
			ft_strlcat(data->result, data->remaining, ft_strlen(data->result)
					+ ft_strlen(data->remaining) + 1);
			free(data->remaining);
			return (data->result);
		}
		env_list = env_list->next;
	}
	return (ft_strremove(ft_strdup(str), 0, size));
}


// Iterates over a word string and expend variables
void	parsing_loop(t_data *data, char **word, t_env *env_list)
{
	int		before;
	char	*expended;
	char	*str;

	str = *word;
	while (*str)
	{
		expended = NULL;
		if (*str == '$')
		{
			before = str - *word + 1;
			expended = expen(data, str, env_list);
			data->new_str = malloc(ft_strlen(*word) + ft_strlen(expended) + 1);
			if (!data->new_str)
				ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PARSER);
			ft_strlcpy(data->new_str, *word, before);
			ft_strlcat(data->new_str, expended, ft_strlen(data->new_str)
					+ ft_strlen(expended) + 1);
			free(expended);
			free(*word);
			*word = data->new_str;
			if (!*word)
				ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PAR_NEW);
			str = *word + before -1;
			while (*str + 1 == '$')
				str++;
		}
		if (*str)
			str++;
	}
}

// Iterates over the list and applies variable expansion for each
t_lexer	*parsing(t_data *data, t_env *env_list)
{
	t_lexer	*lexer_list;

	lexer_list = data->lexer_list;
	while (lexer_list)
	{
		if (!check_sq(lexer_list->word))
			parsing_loop(data, &(lexer_list->word), env_list);
		if (lexer_list->word)
			lexer_list->word = clean_quote(data, lexer_list->word);
		lexer_list = lexer_list->next;
	}
	return (data->lexer_list);
}
