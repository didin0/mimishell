/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:22 by rsainas           #+#    #+#             */
/*   Updated: 2024/03/20 06:19:52 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	peek_list_from(t_lexer *node)
{
	t_lexer *temp;
	int peek_type;

	peek_type = node->type;
	temp = node->next;
	while (temp->next)
	{		
		if (temp->type == peek_type)//type found
			return (1);	
		temp = temp->next;
	}
	return (0);//did not find or @ tail node
}
