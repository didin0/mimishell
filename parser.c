/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/25 14:25:17 by mabbadi          ###   ########.fr       */
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
int check_sq(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '\'')
            return 1;
        i++;
    }
    return 0;
}
int check_dq(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '\"')
            return 1;
        i++;
    }
    return 0;
}


/* 
        aa  - b . 
 */
char *find_key_in_str(char *str, t_env *env_list)
{
   str = clean_quote(str); 
   int total_len;
   str++;
    while (env_list)
    {
        int size = ft_strlen(str);
        char *presult = ft_calloc(size,1);
        presult  =  ft_strnstr(str, env_list->key, ft_strlen(env_list->key));
        if (presult != NULL && ft_strncmp(str, presult, ft_strlen(str)) == 0)
        {
            if (ft_strncmp(env_list->key, presult, ft_strlen(str)) != 0)
                return NULL;
            int pos = presult - str;
            char *new_value = env_list->value;
            int new_value_len = ft_strlen(new_value);
            int key_len = ft_strlen(env_list->key);
            if(new_value_len > key_len)
                total_len = size + (new_value_len - key_len);
            else 
                total_len = size + (key_len - new_value_len);
            char *modified_str = malloc(total_len + 1);
            if (modified_str == NULL)
                return NULL;
            ft_strlcpy(modified_str, str, pos); // Copy in modified_str what is before the '$'
            ft_strlcat(modified_str, new_value, total_len + 1); // Add in modified_str the expended variable
            ft_strlcat(modified_str, str + (pos + key_len), total_len + 1); // Add in modified_str the remaining string
            return modified_str;
        }
        env_list = env_list->next;
    }
    return NULL;
}

int count_$(char *str)
{
    int i = 0;
    int j = 0;
    while(str[i])
    {
        if(str[i] == '$')
            j++;
        i++;
    }
    return (j);
}

// echo " $HOME d $HOME"
char *expander(char *str, t_env *env_list)
{
    int i = 0;
    int j = 0;
    char *result = malloc(sizeof(char *) + 1);
    char *tmp;
    int variables = count_$(str);
    int size = ft_strlen(str);
    while(str[i])
    {
        if(str[i] == '$')
        {
                    result = find_key_in_str(str, env_list);
                    if(result)
                        return result;
                    else if (!result)
                    {
                        if(check_dq(str))
                        {
                            result = ft_substr(str, 0, i);
                            j = i;
                            while(str[j])
                            {
                                j++;
                                if(str[j] == '\"' || str[j] == ' ')
                                    break;
                            }
                            tmp = ft_substr(str, j, size - j);
                            ft_strlcat(result, tmp, (ft_strlen(result) + ft_strlen(tmp) + 1));
                            return (result);
                        }
                        return (ft_substr(str, 0, i));
                    }
        }
        i++;
    }
    return str;
}

/*
@1rst if		return in case of $? as a special case of expansion
*/

t_lexer *parsing(t_data *data, t_env *env_list)
{
    t_lexer *head = data->lexer_list;
    t_lexer *tmp = head;

	if (!ft_strncmp(data->lexer_list->word, "$?",
		ft_strlen(data->lexer_list->word)))
		return (NULL);
	while (tmp)
    {
        int variables = count_$(tmp->word);
        int j = 0;
        int size;
        char *temp;
        if(!check_sq(tmp->word))
        {
            int i = 0;
            char **tab1 = ft_split(tmp->word,'$'); 
        
            while(tab1[i])
            {
            //    printf("** %s\n",tab1[i]);
                char *dol;
                dol = malloc(sizeof(char *) * sizeof(char *) + 1);
                tab[i] = malloc(sizeof(char *) * sizeof(char *) + 1);
                dol = ft_strdup("$");
                size = ft_strlen(tab1[i]) + ft_strlen(dol) + 1;
                ft_strlcat(dol, tab1[i], size); 
                ft_strlcpy(tab1[i], dol, size);
                i++;

            }
            while(j < variables)
            {
                if ((j == variables -1) && (variables != i)) 
                {
                    // NOT WORKING ??? MALLOC SIZE TOO SMALL ???
                    printf("OK 1\n");
                    char *dol;
                    dol = ft_strdup("HELLO");
                    // printf("dol : %s\n", dol);
                    // printf("word b: %s\n", tmp->word);
                    ft_strlcat(tmp->word, dol, ft_strlen(tmp->word) + 1);
                    // printf("word a: %s\n", tmp->word);
                }
                else if (j == 0)
                {
                    printf("OK 2\n");
                    tmp->word = expander(tab1[j], env_list);
                    // printf("tab1[%d] : %s\n", j, tab1[j]);
                }
                else
                {
                    printf("OK 3\n");
                    temp = expander(tab1[j], env_list);
                    size = ft_strlen(tmp->word) + ft_strlen(temp) + 1;
                // printf("tmp->word : %s\n", tmp->word);
                    ft_strlcat(tmp->word, temp, size);
                }
                j++;
            }
        }
        tmp->word = clean_quote(tmp->word);
        tmp = tmp->next;
    }
    data->lexer_list = head;
    return data->lexer_list;
}
