/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/09 19:03:15 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Clean all quotes of the same type and expend if you meet double quote
char	*clean_quote(char *str)
{
	int		i;
	int		j;
	char	*result;
	short	dq;
	short	sq;

	i = 0;
	dq = 0;
	sq = 0;
	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	dq = 0, sq = 0;
	while (str[i])
	{
		if ((str[i] == '\"' && !sq) || (str[i] == '\'' && !dq))
		{
			if ((dq && str[i] == '\'') || (sq && str[i] == '\"'))
			{
				result[j++] = str[i];
				dq = 0;
				sq = 0;
			}
			else if (str[i] == '\"')
				dq = 1;
			else
				sq = 1;
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char *expander(char *str, t_env *env_list)
{
    int i = 0;
    int j = 0;
    char *result = malloc(sizeof(char *) + 1);
    while(str[i])
    {
        if(str[i] == '$')
        {
            
        }
        i++;
    }
    return result;
}

int	main(int argc, char **argv, char **envp)
{
	char *str;
	char *cleaned_str = malloc(sizeof(char *));
	char *expended_str = malloc(sizeof(char *));
    t_env	*env_list = get_env_to_list(envp);

	str = ft_strdup("\'\"he\'l\'lo\"\'");
	printf("%s\n", str);
	cleaned_str = clean_quote(str);
	// expended_str = expander(cleaned_str, env_list);
	printf("%s\n", cleaned_str);

	return (0);
}