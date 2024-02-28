/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:00:39 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/28 17:01:50 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_substr_to_list(t_lexer **lexer_list, char *buff, char *line, int i,
		int ibis)
{
	buff = ft_substr(line, ibis, i - ibis);
	ft_lstlex_add_back(lexer_list, ft_lstlex_new(buff));
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
				add_substr_to_list(lexer_list, buff, line, i, ibis);
			if (is_token(line, i) == 2)
			{
				buff = ft_substr(line, i, 2);
				i++;
			}
			else
				buff = ft_substr(line, i, 1);
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
				add_substr_to_list(lexer_list, buff, line, i, ibis);
				break ;
			}
			add_substr_to_list(lexer_list, buff, line, i, ibis);
			ibis = i + 1;
		}
		i++;
	}
	return (*lexer_list);
}

void	lexing(t_data *data)
{
	data->lexer_list = ft_calloc(sizeof(t_lexer), 1);
	data->lexer_list = splitting_lexer(data->line, &data->lexer_list);
}
