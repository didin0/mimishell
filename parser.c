/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:16:49 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/06 17:27:45 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_new(t_data *data, char **word, char *expanded, int before)
{
	data->new_str = malloc(ft_strlen(*word) + ft_strlen(expanded) + 1);
	if (!data->new_str)
		adv_error(data, ERR_MALLOC_PAR, STDERR_FILENO, FREE_M);
	re_bin(data->new_str, 0);
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
			*word = data->new_str;
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
@EXP_STATUS			in case first token in list is $?
*/

void	parsing(t_data *data, t_env *env_list)
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
}
