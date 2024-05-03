/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:51 by rsainas           #+#    #+#             */
/*   Updated: 2024/05/03 13:18:36 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance to mimic bash in some subsequent redirections and file names
 */

void	create_empty_file(char *name)
{
	int	fd;

	fd = open(name, O_CREAT, S_IRUSR | S_IWUSR);//TODO open fail -1
	close(fd);
}

/*
@glance		open files, redirect output/input, this is called in child process
			so all redirections are reset after child collected by waitpid().
@O_TRUNC	if file exists, clear its content
*/

void	redir_fd(t_data *data, t_lexer *node)
{
	int		fd;
	t_lexer	*temp;

	fd = -1;
	temp = node;
	if (temp->type == REDIR_OUT)
		fd = open(temp->next->word, OPEN_FLAGS | O_TRUNC, OPEN_RIGHTS);
	else if (temp->type == REDIR_OUT_APP)
		fd = open(temp->next->word, OPEN_FLAGS | O_APPEND, OPEN_RIGHTS);
	else if (temp->type == REDIR_IN)
		fd = open(temp->next->word, O_RDONLY);
	if (fd == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO
	else if (temp->type == REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO
	}
	else if (temp->type == REDIR_OUT || temp->type == REDIR_OUT_APP)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//			ft_error(data);//TODO
	}
	close(fd);
}

/*
@open	previous open enables to use the fd only for writing.
 */

static	void	redir_temp_file_fd(t_data *data, int fd)
{
	fd = -1;
	fd = open("here_doc_temp", O_RDONLY);
	if (fd == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO
	if (unlink("here_doc_temp") == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO
	//TODO free readline memory?
	close(fd);
//	signal(SIGINT, sigint_handler);
}

/*
@glance			store delimiter string. open a temp file and loop to store lines
				from user prompt.
@!here_line		EOF, ctrl-D case
@signal			for for SIGINT to pass throught to readline.
*/

void	here_doc_in(t_data *data, t_lexer *node)
{
	char	*delimiter;
	char	*here_line;
	int		fd;

	if (check_heredoc_meaning(node))
	{
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
		printf("Choose an unique delimier name\n");
//		ft_error(data);//TODO free, delimiter matches a commad
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_DFL);
	delimiter = node->next->word;
	here_line = NULL;
	fd = -1;
	fd = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO	
	while (1)
	{
		here_line = readline("\033[37m> \033[m ");
		if (!here_line)
		{
			if (ft_putchar_fd('\n', 1) < 0)
				ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//				ft_error(data);//TODO message write failed, clean, exit
			break ;
		}
		if (!adv_strncmp(here_line, delimiter))
			break ;
		write(fd, here_line, ft_strlen(here_line));
		write(fd, "\n", 1);
	}
	redir_temp_file_fd(data, fd);	
}

void	expand_status(t_data *data)
{
	ft_putnbr_fd(data->exit_status, 1);
	if (ft_putstr_fd(": command not found\n", 1) < 0)
		ft_error(data, ERR_MALLOC, STDERR_FILENO, FREE_PAR);
//		ft_error(data);//TODO msg write failed
}
