// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/01 12:06:55 by mabbadi           #+#    #+#             */
// /*   Updated: 2024/03/06 11:40:47 by mabbadi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	show(t_env *list)
// {
// 	while (list)
// 	{
// 		printf("key = %s value = %s\n", list->key, list->value);
// 		list = list->next;
// 	}
// }

// char **get_paths(t_env *env_list)
// {
//     char **paths;
//     char *path;
//     while(env_list->next)
//     {
//         if(ft_strncmp(env_list->key, "PATH", 4) == 0)
//             paths = ft_split(env_list->value, ':');
//         env_list = env_list->next;
//     }
//     return paths;
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_list;

// 	env_list = get_env_to_list(envp);

//     char **paths = get_paths(env_list);
//     int i = 0;
//     while(paths[i])
//     {
//         printf("%s\n", paths[i]);
//         i++;
//     }

// 	// show(env_list);
// 	return (0);
// }
