/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:30 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/16 17:04:10 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	freetab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void test(t_list *command, char *line)
{
	t_list *tmp = NULL;
	int i;
	while(1)
	{
		i = 0;
		char **words;
		line = readline("minishell:");
		words = ft_split(line, ' ');
		free(line);
		while(words[i])
		{
			ft_lstadd_back(&command, ft_lstnew(words[i]));
			// printf("%s\n", words[i]);
			// free(words[i]);
			i++;
		}
		free(words);
		tmp = command;
		while (tmp != NULL)
		{
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
	}
}

int main(int argc, char **argv)
{
	char *line = NULL;
	t_list *command = NULL;
	test(command, line);

		// ft_lstclear(&command, free);
		// ft_lstclear(&tmp, free);
		// freetab(words);
	system("leaks minishell");
	return 0;
}
