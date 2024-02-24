/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:36:10 by mabbadi           #+#    #+#             */
/*   Updated: 2024/02/23 22:10:35 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_lexer
{
	char			*word;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_data
{
	char			*line;
	t_lexer			*lexer_list;
}					t_data;

void	freetab(char **str);

// List
t_lexer	*ft_lstlex_new(void *word);
void	ft_lstlex_add_back(t_lexer **lst, t_lexer *new);
void add_substr_to_list(char *buff, char *line, int i, int ibis);

#endif