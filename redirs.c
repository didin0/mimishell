/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:51 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/14 08:33:51 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_empty_file(t_data *data, char *name)
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
	int	fd;
	t_lexer *temp;

	fd = -1;
	temp = node;
	if (temp->type == REDIR_OUT)
		fd = open(temp->next->word, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (temp->type == REDIR_OUT_APP)
		fd = open(temp->next->word, O_WRONLY | O_CREAT | O_APPEND,
			   	S_IRUSR | S_IWUSR);
	else if (temp->type == REDIR_IN)
		fd = open(temp->next->word, O_RDONLY);
	if (fd ==-1)	
		ft_error(data);//TODO	
	else if (temp->type == REDIR_IN)	
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_error(data);//TODO
	}
	else if (temp->type == REDIR_OUT || temp->type == REDIR_OUT_APP)	
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_error(data);//TODO
	}
	close(fd);
}
	
/*
@glance		store delimiter string. open a temp file and loop to store lines
			from user prompt.
@2nd open	first open enables to use the fd only for writing.
*/

void	here_doc_in(t_data *data, t_lexer *node)
{
	char *delimiter;
	char *here_line;
	int fd;

	delimiter = node->next->word;
	here_line = NULL;
	fd = -1;
	fd = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)	 
	  	ft_error(data);//TODO	
	while (1)
	{
		here_line = readline("\033[37m> \033[m ");
		if (!here_line)//EOF ctrl-D case
		{	
			if (ft_putchar_fd('\n', 1) < 0)
					ft_error(data);//TODO message write failed, clean, exit
			break;
		}
		if (!ft_strncmp(here_line, delimiter, ft_strlen(here_line)))
			break;
		write(fd, here_line, ft_strlen(here_line));
		write(fd, "\n", 1);
	}
	fd = -1;
	fd = open("here_doc_temp", O_RDONLY);
	if (fd == -1)	 
	  	ft_error(data);//TODO
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error(data);//TODO
	if (unlink("here_doc_temp") == -1)
		ft_error(data);//TODO
	//TODO free readline memory?
	close(fd);
}

void	expand_status(t_data *data)
{
	ft_putnbr_fd(data->exit_status, 1);
	if (ft_putstr_fd(": command not found\n", 1) < 0)
		ft_error(data);//TODO msg write failed
}

/*
@ glance	loop the token count times, call redirection functions
*/
//TODO count all redirections within between pipes.
void	make_redirections(t_data *data, t_lexer *cur_node)
{
	int	count;

	count = count_tokens(data);
	printf("cur node %s, type %d, count %d\n", cur_node->word, cur_node->type, count);
	while (cur_node->next && count > 0)
	{
		if (cur_node->type == REDIR_OUT || cur_node->type == REDIR_OUT_APP
		|| cur_node->type == REDIR_IN)
			redir_fd(data, cur_node);
		else if (cur_node->type == HERE_DOC)
			here_doc_in(data, cur_node);
		if (cur_node->next->next && is_token(cur_node->next->next->word, 0))
			//accessing memory where I should not, invalid read TODO
			cur_node = cur_node->next->next;
		count--;	
	}
//	if (cur_node->type == EXP_STATUS)
//			expand_status(data, cur_node);

}
