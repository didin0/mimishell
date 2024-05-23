/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/05/23 10:56:44 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
echo $OLDPWD
echo $USER$USER
echo $USER$
echo $USER" $USER"
echo $USER " $USER "
echo '"$USER"'
echo "'$USER'"


*/
// Clean all quotes of the same type and expend if you meet double quote
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
		ft_error(data, ERR_MALLOC_PAR_U, STDERR_FILENO, FREE_PAR_U);
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
    free(str);
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

int count_$(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	return (j);
}
