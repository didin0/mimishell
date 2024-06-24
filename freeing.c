/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:50 by mabbadi           #+#    #+#             */
/*   Updated: 2024/06/24 14:22:48 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
all paths
main -> ctrl-D, !data.line //no leaks
main : linebeak -> ctrl-D 2nd if //no leaks
main : spaces -> ctrl-D // no leaks
main : asd -> lexing -> lexer_list = NULL // no leaks

*/
/*
void	free_env_list(t_env *head)
{
	t_env	*node;

	while (head)
	{
		node = head;
		head = head->next;
		free(node->key);
		free(node->value);
		free(node);
	}
}
*/
void	free_lexer_list(t_data *data)
{
	t_lexer	*node;

	while (data->lexer_list)
	{
		node = data->lexer_list;
		data->lexer_list = data->lexer_list->next;
		free(node->word);
		free(node);
	}
}

/*
free a null terminated 3D char array
*/

void	free_3d_array(char ***str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free_array(str[i++]);
	}
	free(str);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_int_array(int **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	adv_error(t_data *data, const char *msg, int fd, int flag)
{
	(void)data;
	if (flag != EXIT_NO_ERROR && flag != NO_EXIT_NO_MSG)
		ft_putstr_fd("Error: ", fd);
	ft_putstr_fd((char *)msg, fd);
	re_bin(NULL, 1);
	if (flag == EXIT_NO_ERROR || flag == FREE_M)
		re_bin_prompt(NULL, 1);
	if (flag == EXIT_NO_ERROR)
		exit(data->exit_status);
	if (flag == FREE_ENV || flag == FREE_FORK || flag == EXIT || flag == FREE_M)
		exit(EXIT_FAILURE);
}
