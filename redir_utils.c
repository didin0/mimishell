/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:15:45 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/22 16:27:49 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if the cmd[i] contains any of the redirection tokens
// do redirections, refine cmd: take out redirection and file name token,
// store curr node.i
// rely on the assumption that the first token in a command.

t_lexer *array_contains_redir(char **cmd, t_data *data)
{
	t_lexer *node;
	
	node = data->lexer_list;
	while (data ->lexer_list)
	{
		if (is_token(node->word, 0))
			if (node->type == REDIR_OUT)
				create_empty_file(data, node->next->word);
//			node = node->next->next;//traverse 2 nodes
		}
		else if (is_token(cur_node->word, 0))//in case token
			break;
		cmd[i] = ft_strdup(cur_node->word);
//		printf("char **cmd where I look at cmd[i] %c \n", cmd[i][2]); 
		cur_node = cur_node->next;
		i++;

	
	}

	return (node);
}

char	**clean_cmd_redir_fd(char **cmd, t_data data)
{
	t_lexer *node;

	node = array_contains_redir(char **cmd, t_data *data)
		
		make_redirections(data, cur_node);//ie a node where the redir token is
}


