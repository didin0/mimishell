/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:36:10 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/22 14:20:28 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>//for add_history on linux
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>//open
# include <sys/wait.h>//for waitpid on linux

#define PIPE 5
#define REDIR_IN 40
#define HERE_DOC 400
#define REDIR_OUT 41
#define REDIR_OUT_APP 411
#define	F_FILE 10
#define	ASSIGN 0
#define	ASK 1

// linked list to copy the $ENV variable
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// linked list to handle user input
// type 0 builtin TODO
//type 1 cmd, 2 cmd option, 3 cmd term/argument grep AAA grep a"asd 1"a
// 31 cmd argument properly double quoted grep "AAA"
// 32 cmd argument properly single quoted grep '<' 
// 40 redirect input 41 redirect output 400 heredoc redirect input between
// 411 redirect output in append mode
// 5 pipe, 6 exit status expansion, variable to be expanded, 10 file

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
	int		exit_status;
}					t_data;

// Utils
void	free_array(char **str);
void	init_data(t_data *data, t_lexer *lexer_list);
void	ft_error(t_data *data);

// List
t_lexer				*ft_lstlex_new(void *word);
void				ft_lstlex_add_back(t_lexer **lst, t_lexer *new);
void	show_list(t_lexer *lexer_list);
int	peek_list_from(t_lexer *node);

// Env
t_env				*get_env_to_list(char **envp);
char				**get_paths(t_env *env_list);

// Exec
void    execution(t_data *data, t_env *env_list);
char    *find_good_path(char **cmd, char **paths);
int	count_tokens(t_data *data);
void	stat_from_waitpid(t_data *data, pid_t pid1);
t_lexer	*keep_cur_node(t_lexer *cur_node, int i);
void	print_str_array(char **array, int len);

// Lexer
void	lexing(t_data *data);
t_lexer	*splitting_lexer(char *line, t_lexer **lexer_list);
int	add_substr_to_list(t_lexer **lexer_list, char *buff, char *line, int i, int ibis);
int	is_token(char *c, int i);
void	token_type(t_data *data, t_env *env_list);
int	is_cmd(t_lexer *token, t_env *env_list);
int	all_tokens_categorized(t_lexer *temp);
int	ft_strchr_from(char *s, char c, int i);
int	ft_strchr_end(char *s, char c, int i);
int	is_quote_closed(char *s, char c);
int is_builtin(t_data *data, char *word);


// Parser
t_lexer *parsing(t_data *data, t_env *env_list);

//Redirections
void	make_redirections(t_data *data, t_lexer *node);
void	redir_fd(t_data *data, t_lexer *node);
void	create_empty_file(t_data *data, char *name);
void	here_doc_in(t_data *data, t_lexer *node);
#endif 
