// // /* ************************************************************************** */
// // /*                                                                            */
// // /*                                                        :::      ::::::::   */
// // /*   test.c                                             :+:      :+:    :+:   */
// // /*                                                    +:+ +:+         +:+     */
// // /*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
// // /*                                                +#+#+#+#+#+   +#+           */
// // /*   Created: 2024/03/01 12:06:55 by mabbadi           #+#    #+#             */
// // /*   Updated: 2024/03/06 11:40:47 by mabbadi          ###   ########.fr       */
// // /*                                                                            */
// // /* ************************************************************************** */

// #include "minishell.h"

// int main(int argc, char **argv, char **envp)
// {

//     char	**cmd = malloc(5 * sizeof(char *));
//     char	**cmd2 = malloc(5 * sizeof(char *));
//     char    **paths;
//     char    *path;
//     char    *path2;
// 	pid_t	pid1;
//     int     fd[2];

// 	int code;

//     char **splited_paths = ft_split(getenv("PATH"), ':');

// 	cmd[0] = ft_strdup("grep");
//     cmd[1] = ft_strdup("env");

//     cmd2[0] = ft_strdup("ls");
//     path = find_good_path(cmd, splited_paths);
//     path2 = find_good_path(cmd2, splited_paths);
    
//     if (pipe(fd) < 0)
//         return 2;
//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
// 	    // close(fd[1]);
//         execve(path2, cmd2, NULL);
//     }
//     else
//     {
//         dup2(fd[0], STDIN_FILENO);
// 	    // close(fd[0]);
//         execve(path, cmd, NULL);
//         waitpid(pid1, NULL, 0);
//     }
//     return 0;
// }