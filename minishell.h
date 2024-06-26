/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:36:10 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/06 23:48:37 by rsainas          ###   ########.fr       */
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
# include <errno.h>//error number codes
# include <limits.h>//PATH_MAX
# include <signal.h>//signal
# include <stdbool.h>//bool in lexing

# define BUILTIN 0
# define COMMAND 1
# define PIPE 5
# define REDIR_IN 40
# define HERE_DOC 400
# define REDIR_OUT 41
# define REDIR_OUT_APP 411
# define EXP_STATUS 6
# define F_FILE 10
# define OTHER 3
# define ASSIGN 0
# define ASK 1
# define EMPTY 10000

// Error defines
# define ERR_WRITE_FAIL "Write call failed\n"
# define ERR_MALLOC "GENEREAL Malloc failed\n"
# define ERR_MALLOC_ENV "Malloc failed, env.c\n"
# define ERR_MALLOC_L "Malloc failed, lexing.c\n"
# define ERR_MALLOC_LUS "Malloc failed, lexing_utils_split.c\n"
# define ERR_MALLOC_LUA "Malloc failed, lexing_utils_add.c\n"
# define ERR_MALLOC_LU "Malloc failed, lexing_utils.c\n"
# define ERR_MALLOC_PATH "Malloc failed, find_paths.c\n"
# define ERR_MALLOC_LI "Malloc failed, list.c\n"
# define ERR_MALLOC_PAR "Malloc failed, parser.c\n"
# define ERR_MALLOC_PAR_U "Malloc failed, parser_utils.c\n"
# define ERR_READLINE "Readline fail of EOF sent to process\n"
# define ERR_QUOTE_CLOSE "Quotes shall be closed.\n"
# define ERR_PATH "PATH env missing.\n"
# define ERR_MEANING "Meaning/command missing or with many meanings\n"
# define ERR_MALLOC_EX_UA "Malloc failed, exec_utils_add.c\n"
# define ERR_MALLOC_EX "Malloc failed, execution.c\n"
# define ERR_MALLOC_BU_EX "Malloc failed, builtin_export.c\n"
# define ERR_MALLOC_BU_CD "Malloc failed, builtin_cd.c\n"
# define ERR_MALLOC_RE_U "Malloc failed, redir_utils.c\n"
# define ERR_EX_ARG "Export needs = and alphanumerical chars prior =\n"
# define ERR_CD_ARG "cd: no-such/check path, dir / chdir call fail\n"
# define ERR_CD_MAX "cd: too many arguments\n"
# define ERR_CD_HOME "cd: HOME env missing\n"
# define ERR_CD_GET "cd: PWD env missing / getcwd call failed\n"
# define ERR_OPEN "Open/close/dup2/unlink failed in redirs.c\n"
# define ERR_HERE "Choose an unique heredoc delimier name\n"
# define ERR_FORK "Fork call failed in execution.c\n"
# define ERR_WAIT "Wait/reaping failed in exec_utils.c\n"
# define ERR_EXIT "exit\n"
# define ERR_EXIT_ARG "exit: numeric argument required\n"
# define ERR_EXIT_MAX "exit: too many arguments\n"
# define ERR_UNSET "UNSET needs an argument\n"
# define EXIT 0
# define NO_EXIT 1
# define EXIT_NO_ERROR 3
# define FREE 2
# define FREE_ENV 2
# define FREE_M 4
# define NO_EXIT_NO_MSG 5
# define FREE_FORK 32

extern pid_t	g_child_pid;

// linked list to copy the $ENV variable
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// linked list to handle user input
typedef struct s_lexer
{
	char			*word;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

// GENERAL STRUCT
typedef struct s_data
{
	char				*line;
	t_lexer				*lexer_list;
	int					exit_status;
	char				***cmd;
	int					cmd_count;
	int					pipe_count;
	int					list_size;
	int					pwd_flag;
	struct sigaction	sa;
	t_env				*env_list;
	char				*buff;
	char				**builtin_names;
	char				**paths;
	char				*final_path;
	char				**asked_paths;
	pid_t				*pids;
	char				*new_path;
	int					**pipefd;
	char				*result;
	char				*remaining;
	char				*new_str;
	char				*str;
	char				**new_env;
}					t_data;

//Lexing splitting local struct
typedef struct s_stat
{
	int				i;
	int				ibis;
}					t_stat;

/*Categrization of tokens
 type 0 builtin
 type 1 cmd, 2 cmd option, 3 cmd term/argument grep AAA grep a"asd 1"a
 31 cmd argument properly double quoted grep "AAA"
 32 cmd argument properly single quoted grep '<' 
 40 redirect input 41 redirect output 400 heredoc redirect input between
 411 redirect output in append mode
 5 pipe, 6 exit status expansion, 7 variable to be expanded
*/

// Utils
void	init_data(t_data *data);
void	ft_error_errno(char **cmd);
void	free_ptr(void *ptr);
void	ft_lstdelone_bin(t_list *lst, void (*del)(void*));

// List
t_lexer	*ft_lstlex_new(t_data *data, void *word);
void	ft_lstlex_add_back(t_lexer **lst, t_lexer *new);
void	build_builtin_names(t_data *data);
void	create_node_is_token(t_data *data, t_stat *stat);
int		create_node_space_term(t_data *data, t_stat *stat);
int		create_node_quotes(t_data *data, t_stat *stat);
void	str_to_list(t_data *data, t_stat *stat);
void	show_list(t_lexer *lexer_list);
void	show_env_list(t_env *list);

// Env
char	**ft_adv_split(char const *s, char c);
t_env	*get_env_to_list(t_data *data, char **envp);
void	get_paths(t_data *data, t_env *env_list);
t_env	*create_env_node(t_data *data, char *key, char *value);
void	add_to_end(t_env **head, t_env *new_node);
int		check_path(t_data *data);

// Exec
int		check_meaning(t_data *data);
void	allocate_cmd(t_data *data);
int		count_token_type(t_data *data, int type1, int type2);
void	create_pipes(t_data *data);
void	organize_good_paths(t_data *data, t_env *env_list);
int		execution(t_data *data, t_env *env_list);
char	*find_good_path(t_data *data, char *cmd);
void	alloc_pids(t_data *data);
int		adv_strncmp(const char *s1, const char *s2);
void	exec_child(t_env *env_list, t_data *data, pid_t *pids);
void	parent_close_all_fds(t_data *data);
void	redirect_close_fds(t_data *data, int i);
void	close_unused_fds(t_data *data, int i);
int		count_tokens(t_data *data);
void	stat_from_waitpid(t_data *data, pid_t *pids);
t_lexer	*keep_cur_node(t_lexer *cur_node, int i);
void	update_cur_node(t_data *data, int i);
void	print_str_array(char **array, int len);

// Lexer
int		lexing(t_data *data);
int		is_token(char *c, int i);
void	token_type(t_data *data, t_env *env_list);
int		is_cmd(t_data *data, t_lexer *token, t_env *env_list);
int		is_token_path(char *cmd);
int		all_tokens_categorized(t_lexer *temp);
int		is_quote_closed(char *s, char c);
int		is_builtin(t_data *data, char *word);

// Parser
void	parsing(t_data *data, t_env *env_list);
char	*expen(t_data *data, char *str, t_env *env_list);
char	**ft_new_split(char const *s, char c);
int		check_sq(char *str);
char	*clean_quote(t_data *data, char *str);
char	*ft_strremove(t_data *data, char *s, int start, int n);
int		key_size(char *str);

//Redirections

void	look_for_redirs(t_data *data, int i);
void	redir_fd(t_data *data, t_lexer *node);
void	clean_cmd_from_redir(t_data *data, t_lexer *node, int i);
void	create_empty_file(char *name);
void	here_doc_in(t_data *data, t_lexer *node);
int		check_heredoc_meaning(t_lexer *node);
int		adv_list_size(t_lexer *list);

//Builtins
int		exec_builtin_parent(t_data *data, char **cmd, t_env *env_list);
int		exec_builtin_child(t_data *data, char **cmd, t_env *env_list);
void	pwd_builtin(t_data *data, t_env *env_list);
void	env_builtin(t_data *data, t_env *env_list);
void	cd_builtin(t_data *data, char **cmd, t_env *env_list);
void	cd_also_path(t_data *data, char **cmd, t_env *env_list);
void	export_builtin(t_data *data, char **cmd, t_env *env_list);
char	*our_get_env(t_env *env_list, char *env);
void	unset_builtin(t_data *data, char **cmd, t_env *env_list);
int		ft_isdigit_sign(char *str);
void	exit_builtin(t_data *data, char **cmd);
void	expand_status(t_data *data);

//Signals
void	init_signals(t_data *data);
void	sigint_handler(int signum);
void	show_cmd(char ***cmd, t_data *data);

//Garbage collection, recycle bin
void	*re_bin(void *ptr, bool clean);
void	*re_bin_prompt(void *ptr, bool clean);
void	adv_error(t_data *data, const char *msg, int fd, int flag);
#endif 
