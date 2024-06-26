/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adv_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:16:49 by abaccari          #+#    #+#             */
/*   Updated: 2024/06/05 21:30:24 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance 	calculate the number of words within a string to be splitted
			fix to 2 for this project, since envp seams to have one that less
*/

static int	numwords(char const *s, char c)
{
	int	i;
	int	word_num;

	i = 0;
	word_num = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			word_num++;
		i++;
	}
	word_num = 2;
	return (word_num);
}

static char	*alloc_substr(const char *s, int start, int end)
{
	char		*str;
	static int	word = 0;

	str = ft_calloc(sizeof(char), (end - start + 2));
	if (!str)
		return (NULL);
	re_bin_prompt(str, 0);
	ft_strlcpy(str, (s + start), end - start + 2);
	word++;
	return (str);
}

// Split *s en sous chaine et return 1 or 0
static int	split_words(char **result, char const *s, char c, int word)
{
	int		start_i;
	int		end_i;
	int		flag;

	end_i = 0;
	start_i = 0;
	flag = 0;
	while (s[end_i])
	{
		if ((s[end_i] == c || s[end_i] == 0) && flag == 0)
			start_i = end_i + 1;
		if (((s[end_i + 1] == c || s[end_i + 1] == 0) && flag == 0)
			&& s[end_i] != c)
		{
			result[word] = alloc_substr(s, start_i, end_i);
			if (!result[word])
				return (0);
			word++;
			flag = 1;
			start_i = end_i + 2;
		}
		else if (s[end_i + 1] == 0 && flag == 1)
			result[word] = alloc_substr(s, start_i, end_i);
		end_i++;
	}
	return (word++, result[word] = 0, 1);
}

char	**ft_adv_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), (numwords(s, c) + 1));
	if (!result)
		return (NULL);
	re_bin_prompt(result, 0);
	if (!split_words(result, s, c, 0))
		return (NULL);
	return (result);
}
