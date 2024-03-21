/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:39:15 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/14 21:19:17 by rsainas          ###   ########.fr       */
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

char *find_key_in_str(char *str, t_env *env_list)
{
    while (env_list)
    {
        int size = ft_strlen(env_list->key);
        char *presult = ft_strnstr(str, env_list->key, size);
        if (presult != NULL) // should add a check if there is a single quote ' to not expand the $variable OR check directly on the call of expander
        {
            int pos = presult - str;
            char *new_value = env_list->value;
            int new_value_len = ft_strlen(new_value);
            int remaining_len = ft_strlen(presult + size);
            int total_len = pos + new_value_len + remaining_len;
            char *modified_str = malloc(total_len + 1);
            if (modified_str == NULL)
                return NULL;
            ft_strlcpy(modified_str, str, pos);
            ft_strlcat(modified_str, new_value, total_len + 1);
            ft_strlcat(modified_str, presult + size, total_len + 1);
            free(str);
            return modified_str;
        }
		// else ...... if the $variable is not found it should put nothing instead of the "$variable"
        env_list = env_list->next;
    }
    return NULL;
}

char *expander(char *str, t_env *env_list)
{
    int i = 0;
    int j = 0;
    char *result = malloc(sizeof(char *) + 1);
	char **tmp;
    while(str[i])
    {
        if(str[i] == '$')
        {
			result = find_key_in_str(str, env_list);
			if(result)
				return result;
        }
        i++;
    }
    return str;
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

t_lexer *parsing(t_data *data, t_env *env_list)
{
    t_lexer *head = data->lexer_list;
    t_lexer *tmp = head;

    while (tmp)
    {
//        printf("type : %d\n", tmp->type);
        if(!check_sq(tmp->word))
            tmp->word = expander(tmp->word, env_list);
        tmp->word = clean_quote(tmp->word);
        tmp = tmp->next;
    }
    data->lexer_list = head;
    return data->lexer_list;
}


// int	main(int argc, char **argv, char **envp)
// {
// 	char *str;
//     t_env	*env_list = get_env_to_list(envp);

// 	str = ft_strdup("hello ciao");
// 	printf("%s\n", str);
// 	str = clean_quote(str);
// 	str = expander(str, env_list);
// 	printf("%s\n", str);
// 	// printf("%s\n", expended_str);

// 	return (0);
// }
