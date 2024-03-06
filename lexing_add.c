/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:02:09 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/06 09:35:02 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_data *data)
{
	t_lexer	*temp;
	int ret;
	int	fd;

	temp = data->lexer_list;
	fd = 0;
	while (temp != NULL)
	{
//		if (t_env cmd access) TODO
		if (temp->word[0] == '-')
			temp->type = 2;
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
		fd = open(temp->word, O_RDONLY);
		if (fd != -1)
		{
			temp->type = 6;
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

int	ft_strchr_double(char *s, char c, int i)//find twice
{	
	int	j;

	j = 0;
	while (j <= i)
	{
		s++;
		j++;
	}
	while (*s != (char)c && *s != 0)//stype of string term
	{
		s++;
		i++;
	}
	if (*s == (char)c)
	{
		return (i + 1);//pointer to second "
	}
	else
		return (0);
	return (0);
}
