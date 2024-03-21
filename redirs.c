/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:04:51 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/21 09:42:03 by rsainas          ###   ########.fr       */
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
		{	
			if (fd ==-1)	
				ft_error(data);//TODO
		}
	if  (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(data);//TODO
}
