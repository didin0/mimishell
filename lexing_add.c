/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:02:09 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/11 14:11:46 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_data *data, t_env *env_list)
{
	t_lexer	*temp;
	int	fd;

	temp = data->lexer_list;
	fd = 0;
	while (temp != NULL)
	{
		if (!is_cmd(temp, env_list))
		   	temp->type = 1;
		if (temp->word[0] == '-')
			temp->type = 2;
		else if (ft_strrchr(temp->word,'"'))//todo
			temp->type = 31;
		else if (temp->word[0] == '\'')
			temp->type = 32;
		else if (temp->word[0] == '<' && temp->word[1] == '<')
			temp->type = 400;//input redirection delimiter followwing TODO
		else if (temp->word[0] == '>' && temp->word[1] == '>')
			temp->type = 411;
		else if (temp->word[0] == '<' && temp->word[1] == '\0')
			temp->type = 40;
		else if (temp->word[0] == '>' && temp->word[1] == '\0')
			temp->type = 41;
		else if (temp->word[0] == '|')
			temp->type = 5;
		else if (temp->word[0] == '$')
		{
			if (temp->word[1] == '?')
				temp->type = 6;
			else
				temp->type = 7;
		}
		fd = open(temp->word, O_RDONLY);
		if (fd != -1)
		{
			temp->type = 10;
			close(fd);
		}
		else if (temp->type == 0)
			temp->type = 3;//cmd term
		temp = temp->next;
	}
	temp = data->lexer_list;
	if (all_tokens_categorized(temp) == 1)
//   	ft_error(data);
		printf("token error\n");	
}

int	all_tokens_categorized(t_lexer	*temp)
{
	while (temp != NULL)
	{
		if (temp->type == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ft_strchr_end(char *s, char c, int i)//loop until a pipe and then back till the first
{	
//	printf("Test %d\n", i);
	while (s[i] != '|' && s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
//	printf("i looping backwards %d\n", i);
		i--;
	}
	return (0);
}

/*
@glance			increment the pointer to position i, look for c.
				return c position + 1.
*/

int	ft_strchr_from(char *s, char c, int i)//TODO rewrite not needing j, in case useful func
{	
	int	j;

	j = 0;
	while (j <= i)
	{
		s++;
		j++;
	}
	while (*s != (char)c && *s != 0)
	{
		s++;
		i++;
	}
	if (*s == (char)c)
		return (i);
	else
		return (0);
	return (0);
}



int	is_quote_closed(char *s, char c)
{
	int	count;

	count = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}
