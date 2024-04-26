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
// store curr node.i, give to make_redir function
// rely on the assumption that the first token in a command.

int	adv_listsize(t_lexer *list)
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

static	char **change_cmd(char **cmd, t_data *data, int i)
{
	char **temp;
	t_lexer *node;
	int	j;
	int k;

	temp = ft_calloc(adv_listsize(data->lexer_list), sizeof(char *));
	if (!temp)
		ft_error(data);//TODO malloc failure
	node = NULL;
	if (keep_cur_node(node, ASK))//path for case cat main.c > t1
		node = keep_cur_node(node, ASK);//return node on >
	else
		node = data->lexer_list;
	j = 0;
	if (node != data->lexer_list)//path for case cat main.c | grep void > t2??
	{
		node = data->lexer_list;
		while(node && j < i)
		{
			if (node->type == PIPE)
				j++;
			node = node->next;
		}
		keep_cur_node(node, ASSIGN);//path for case cat main.c > t1

	}
	k = 0;
	while (node && node->type != PIPE)//clean cmd from tokens and file names
	{
		if (is_token(node->word, 0))
			node = node->next->next;//traverse token and file name
		if (is_token(node->word, 0) && node->type != PIPE)
			node = node->next->next;//cat << EOF > t1 also cat <<EOF | grep a
		if (node && node->type != PIPE)
			temp[k] = node->word;
		if (node)
			node = node->next;
		k++	;
	}
	return (temp);
}

static	void  array_contains_redir(char **cmd, t_data *data)
{
	t_lexer *node;

	node = data->lexer_list;
	node = keep_cur_node(node, ASK);
	while (node && node->type != PIPE)
	{
		if (is_token(node->word, 0))
		{
			if (node->type == REDIR_OUT || node->type == REDIR_OUT_APP
			|| node->type == REDIR_IN)
				redir_fd(data, node);
			else if (node->type == HERE_DOC)
				here_doc_in(data, node);
		   /* if (node->type == REDIR_OUT)*/
			/*{*/
				/*create_empty_file(data, node->next->word);*/
				/*keep_cur_node(node, ASSIGN);//for make_redirs to know which type*/
			/*}*/
			//else other redirections

//			return (1);
		}
//			node = node->next->next;//traverse 2 nodes
//		}
//		else if (is_token(cur_node->word, 0))//in case token
//			break;
//		cmd[i] = ft_strdup(cur_node->word);
		node = node->next;
	}	
//	return (0);
}

char	**look_for_redirs(char **cmd, t_data *data, int i)
{
	t_lexer *node;
	
	node = data->lexer_list;
   /* if (array_contains_redir(cmd, data))*/
	array_contains_redir(cmd, data);
//	{
//		cmd = change_cmd(cmd, data);
//		make_redirections(data, keep_cur_node(node, ASK));
		cmd = change_cmd(cmd, data, i);//move the 
//		printf("making redirs\n");	
//		show_cmd(&cmd, data);	
//	}
	return (cmd);
}
