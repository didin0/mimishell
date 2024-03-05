/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:06:55 by mabbadi           #+#    #+#             */
/*   Updated: 2024/03/05 16:52:34 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show(t_env *list)
{
	while (list)
	{
		printf("key = %s value = %s\n", list->key, list->value);
		list = list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
    t_env *env_list = NULL; // Initialize env_list

    int i = 0;
    int j = 0;
    char **str;

    while (envp[i]) {
        t_env *new_env = malloc(sizeof(t_env));
        if (new_env == NULL)
        	return 0;

        str = ft_split(envp[i], '=');
        if (str[0] && str[1])
		{
            new_env->key = ft_strdup(str[0]);
            new_env->value = ft_strdup(str[1]);

            new_env->next = env_list;
            env_list = new_env;
        }

        i++;
	};
    show(env_list);
    return 0;
}
