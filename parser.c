/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:16:49 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/24 10:10:07 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	store_remaining(t_data *data, char *str, t_env *env_list)
{
	data->remaining = ft_strdup(str + ft_strlen(env_list->key));
	if (!data->remaining)
		ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PAR_NEW);
	data->result = malloc(ft_strlen(env_list->value)
			+ ft_strlen(data->remaining) + 1);
	if (!data->result)
		ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PAR_RE);
}

/*
Performs variable expansion in a string based on the environment list
*/

static char	*expen(t_data *data, char *str, t_env *env_list)
{
	int		size;
	char	*temp;

	if (ft_strlen(str) > 1)
		str++;
	size = key_size(str);
	while (env_list)
	{
		if (!ft_strncmp(str, env_list->key, size)
			&& !ft_strncmp(str, env_list->key, ft_strlen(env_list->key)))
		{
			store_remaining(data, str, env_list);
			ft_strlcpy(data->result, env_list->value, ft_strlen(env_list->value)
				+ 1);
			ft_strlcat(data->result, data->remaining, ft_strlen(data->result)
				+ ft_strlen(data->remaining) + 1);
			free(data->remaining);
			return (data->result);
		}
		env_list = env_list->next;
	}
	temp = ft_strdup(str);
	return (ft_strremove(data, temp, 0, size));
}

static void	alloc_new(t_data *data, char **word, char *expanded, int before)
{
	data->new_str = malloc(ft_strlen(*word) + ft_strlen(expanded) + 1);
	if (!data->new_str)
		ft_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_PARSER);
	ft_strlcpy(data->new_str, *word, before);
	ft_strlcat(data->new_str, expanded, ft_strlen(data->new_str)
		+ ft_strlen(expanded) + 1);
}

/*
Iterates over a word string and expend variables
*/

static void	parsing_loop(t_data *data, char **word, t_env *env_list)
{
	int		before;
	char	*expanded;
	char	*str;

	str = *word;
	while (*str)
	{
		if (*str == '$')
		{
			before = str - *word + 1;
			expanded = expen(data, str, env_list);
			alloc_new(data, word, expanded, before);
			free(expanded);
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

/*
Iterates over the list and applies variable expansion for each
*/

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
