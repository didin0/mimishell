/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:51 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/20 14:36:04 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_empty_file(t_data *data, char *name)
{
	int	fd;

	fd = open(name, O_CREAT, S_IRUSR | S_IWUSR);//TODO open fail -1
	close(fd);
}

void	exec_redir_out(t_data *data, t_lexer *node)
{
	int	fd;
	t_lexer *temp;

	temp = node;
	fd = open(temp->next->word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);//TODO open fail -1
//	printf("exec_redir() file name %s and fd %d\n", node->next->word, fd);
		{	
			if (fd ==-1)	
				ft_error(data);//TODO
		}
	if  (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(data);//TODO
}
/*
void	exec_redir_out(t_data *data, t_lexer *node, char **cmd)
{
	t_lexer *temp;

	if (node->next)
		temp = node->next;
	else
		return;
	redir_out(data, cmd, temp);
}
*/

void	redir_out(t_data *data, char **cmd, t_lexer *next)
{
//	t_lexer *temp;
	int	fd;
	
//	show_list(data->lexer_list);	
//	temp = keep_cur_node(data->lexer_list, 1);
	fd = 0;
	printf("redir entered with token %s, type  %d\n", next->word, next->type);
	show_list(data->lexer_list);	
//	if (next->type == F_FILE)//TODO file def is bulletproof, new file.
//	{
		fd = open(next->word, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);//TODO open fail -1
		{	
			if (fd ==-1)	
				printf("Open FAILED\n");//TODO
		}
		printf("fd prior print %d\n", fd);
		write(fd, cmd[1], ft_strlen(cmd[1]));//TODO write fail -1	
		write(fd, "\n", 1);//TODO write fail -1
		close(fd);
		printf("fd after print %d\n", fd);
		keep_cur_node(next->next, 0);//update offset
//	}
	return;
}
