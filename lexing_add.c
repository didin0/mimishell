/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:02:09 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/02 14:54:37 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_data *data)
{
	t_lexer	*temp;
	int ret;

	temp = data->lexer_list;
	while (temp != NULL)
	{
//		if (env cmd) TODO
		if (temp->word[0] == '<' && temp->word[1] == '<')
			temp->type = 400;//input redirection delimiter followwing TODO
		else if (temp->word[0] == '>' && temp->word[1] == '>')
			temp->type = 411;
		else if (temp->word[0] == '<' && temp->word[1] == '\0')
			temp->type = 40;
		else if (temp->word[0] == '>' && temp->word[1] == '\0')
			temp->type = 41;
		else if (temp->word[0] == '|')
			temp->type = 5;	
		else if (open(temp->word, O_RDONLY) != -1)
			temp->type = 6;
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
/*
int	is_redir(char	*token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token[i] == '|')
			return (5);
		if (token[i] == '<' || token[
	}

}
*/

