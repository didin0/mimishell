/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:00:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/01 16:11:15 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Split the user input into multiple node and put it in a linked list.
// The user input is splited in a node when it occur an escape ' '.
// If the user input contain a special token : '|' or '>' or '<' or '>>' or '<<'
// the input is splitted and the token is placed in a separated node.
// token here is a redirection or a pipe but not a command
// @splitting_lexer ibis is the first unporcessed character and 
// i the last char or a word.

int	is_token(char *c, int i)
{
	if (c[i] == '|')
		return (1);
	else if (c[i] == '<' || c[i] == '>')
	{
		if (c[i] == '<' && c[i + 1] == '<')
			return (2);
		if (c[i] == '>' && c[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	return (0);
}

int	add_substr_to_list(t_lexer **lexer_list, char *buff, char *line, int i,
		int ibis)
{
	buff = ft_substr(line, ibis, i - ibis);
	if (!buff)
		return (1);
	ft_lstlex_add_back(lexer_list, ft_lstlex_new(buff));
	return (0);
}

t_lexer	*splitting_lexer(char *line, t_lexer **lexer_list)
{
	int		i;
	int		ibis;
	char	*buff;
	int		aff;

	i = 0;
	ibis = 0;
	while (line && line[i])
	{
		if (is_token(line, i) || line[i] == '\0')
		{
			if (ibis != i)
				if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
					return (NULL);
			if (is_token(line, i) == 2)
			{
				buff = ft_substr(line, i, 2);
				if (!buff)
					return (NULL);
				i++;
			}
			else
				buff = ft_substr(line, i, 1);
			if (!buff)
				return (NULL);
			ft_lstlex_add_back(lexer_list, ft_lstlex_new(buff));
			while (line[i + 1] == ' ')
				i++;
			ibis = i + 1;
		}
		else if (line[i] == ' ' || line[i + 1] == '\0')
		{
			while (line[i + 1] == ' ')
				i++;
			if (line[i + 1] == '\0')
			{
				i++;
				if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
					return (NULL);
				break ;
			}
			if (add_substr_to_list(lexer_list, buff, line, i, ibis) != 0)
				return (NULL);
			ibis = i + 1;
		}
		i++;
	}
	return (*lexer_list);
}

void	lexing(t_data *data)
{
	data->lexer_list = ft_calloc(sizeof(t_lexer), 1);
	if (!data->lexer_list)
		ft_error(data);
	data->lexer_list = splitting_lexer(data->line, &data->lexer_list);
	if (!data->lexer_list)
		ft_error(data);
}
