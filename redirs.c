/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:51 by rsainas           #+#    #+#             */
/*   Updated: 2024/06/24 14:10:51 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@glance		look for redirection tokens, adjust the cmd
*/

void	look_for_redirs(t_data *data, int i)
{
	array_contains_redir(data);
	change_cmd(data, i);
}

int	adv_list_size(t_lexer *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
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
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	else if (temp->type == REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	}
	else if (temp->type == REDIR_OUT || temp->type == REDIR_OUT_APP)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	}
	close(fd);
}

/*
@open	previous open enables to use the fd only for writing.
 */

static void	redir_temp_file_fd(t_data *data, int fd)
{
	fd = -1;
	fd = open("here_doc_temp", O_RDONLY);
	if (fd == -1)
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	if (dup2(fd, STDIN_FILENO) == -1)
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	if (unlink("here_doc_temp") == -1)
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	if (close(fd) == -1)
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
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
		adv_error(data, ERR_HERE, STDOUT_FILENO, FREE_M);
	signal(SIGINT, SIG_DFL);
	delimiter = node->next->word;
	here_line = NULL;
	fd = -1;
	fd = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		adv_error(data, ERR_OPEN, STDERR_FILENO, FREE_M);
	while (1)
	{
		here_line = readline("\033[37m> \033[m ");
		if (!here_line)
		{
			if (ft_putchar_fd('\n', 1) < 0)
				adv_error(data, ERR_WRITE_FAIL, STDERR_FILENO, FREE_M);
			break ;
		}
		if (!adv_strncmp(here_line, delimiter))
			break ;
		write(fd, here_line, ft_strlen(here_line));
		write(fd, "\n", 1);
	}
	redir_temp_file_fd(data, fd);
}
