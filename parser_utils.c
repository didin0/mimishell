/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/06 17:28:32 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Removes a substring from a string starting from a given position
*/

char	*ft_strremove(t_data *data, char *s, int start, int n)
{
	int	len;
	int	i;

	if (!s)
		adv_error(data, ERR_MALLOC_PAR_U, STDERR_FILENO, FREE_M);
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

/*
Determines the size of a key in a string (used in the expansion function)
*/

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

/*
Clean all quotes of the same type and expend if you meet double quote
*/

char	*clean_quote(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*result;
	short	quote;

	i = 0;
	quote = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		adv_error(data, ERR_MALLOC_PAR_U, STDERR_FILENO, FREE_M);
	re_bin(result, 0);
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	check_sq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
