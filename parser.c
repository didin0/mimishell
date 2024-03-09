/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/09 15:56:30 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Clean all quotes of the same type and expend if you meet double quote
char *clean_quote(char *str)
{
    int i = 0;
    int j = 0;
    char *result = malloc(sizeof(char *) + 1);
    short dq = 0;
    short sq = 0;
    while(str[i])
    {
        if(str[i] == '\"' || str[i] == '\'')
        {
            if(str[i] == '\'')
                sq = 1;
            else if(str[i] == '\"')
                dq = 1;
            if(dq == 1 || sq == 1 && str[i] == '\'' || str[i] == '\"')
            {
                result[j] = str[i];
                j++;
            }
            i++;
        }
        else
        {
            result[j] = str[i];
            j++;
        }
        i++;
    }
    return result;
}

int main(void)
{
    char *str;
    char *cleaned_str = malloc(sizeof(char *));

    str = ft_strdup("\'\"hello\"\'");
    printf("%s\n", str);
    cleaned_str = clean_quote(str);
    printf("%s\n", cleaned_str);
    
    return 0;
}