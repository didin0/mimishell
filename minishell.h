/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:36:10 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/02 14:48:28 by rsainas          ###   ########.fr       */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>//open

// linked list to copy the $ENV variable
typedef struct s_env
{
	char 		*key;
	char 		*value;
	struct s_env *next;
}	t_env;

// linked list to handle user input
//type 1 cmd, 2 cmd option, 3 cmd term (grep "AAA"), 
// 40 redirect input 41 redirect output 400 redirect input until
// 411 redirect output in append mode
// 5 pipe, 6 file. 

typedef struct s_lexer
{
	char			*word;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

// GENERAL STRUCT
typedef struct s_data
{
	char			*line;
	t_lexer			*lexer_list;
}					t_data;

// Utils
void	free_array(char **str);
void	init_data(t_data *data, t_lexer *lexer_list);
void	ft_error(t_data *data);

// List
t_lexer	*ft_lstlex_new(void *word);
void	ft_lstlex_add_back(t_lexer **lst, t_lexer *new);

// Lexer
void	lexing(t_data *data);
t_lexer	*splitting_lexer(char *line, t_lexer **lexer_list);
int	add_substr_to_list(t_lexer **lexer_list, char *buff, char *line, int i, int ibis);
int	is_token(char *c, int i);
void	token_type(t_data *data);
int	all_tokens_categorized(t_lexer *temp);

#endif 
