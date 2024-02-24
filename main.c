/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/23 22:16:47 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\0');
}

void add_substr_to_list(char *buff, char *line, int i, int ibis)
{
    buff = ft_substr(line, ibis, i - ibis);
	printf("buff : %s\n", buff);
	free(buff);
}

t_lexer *splitting_lexer(char *line, t_lexer *lexer_list)
{
	int		i;
	int		ibis;
	char	*buff;

	i = 0;
	ibis = 0;
	while (line && line[i])
	{
		if (is_token(line[i]))
		{
			if (ibis != i)
                add_substr_to_list(buff, line, i, ibis);
			buff = ft_substr(line, i, 1);
			printf("buff : %s\n", buff);
			free(buff);
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
				add_substr_to_list(buff, line, i, ibis);
				break ;
			}
			add_substr_to_list(buff, line, i, ibis);
			ibis = i + 1;
		}
		i++;
	}
	printf("line : %s\n", line);
	return (lexer_list);
}

t_lexer *lexing(char *line)
{
	t_lexer *lexer_list = NULL;

	lexer_list = splitting_lexer(line, lexer_list);
	return (lexer_list);
}


int main()
{
	t_data data;

	t_list *command = NULL;
	t_list *tmp = NULL;
	int i;
	int aff = 0;
	while(1)
	{
		data.line =  readline("minishell :");
		data.lexer_list = lexing(data.line);
	}

	//////////////////////////////
	/*
		char **words;
		i = 0;
		data.line = readline("minishell:");
		words = ft_split(data.line, ' ');
		free(data.line);
		while(words[i])
		{
			ft_lstadd_back(&command, ft_lstnew(words[i]));
			// printf("%s\n", words[i]);
			i++;
		}
		tmp = command;
		aff = 0;
		while (tmp != NULL)
		{
			aff++;
			printf("[%d] => %s\n", aff, (char *)tmp->content);
			tmp = tmp->next;
		}
		// freetab(words);
		ft_lstclear(&tmp, free);
		// ft_lstclear(&command, free);
		*/
		// ft_lstclear(&command, free);
	return 0;
}
