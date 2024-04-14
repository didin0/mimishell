/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:32:00 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/14 10:12:57 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int ft_putchar(int c)
{
    return (write(STDOUT_FILENO, &c, 1));  // Simple wrapper around write for a single char
}

void reset_terminal()
{
	printf("reset test 00\n");
    if (tgetent(NULL, getenv("TERM")) < 1) {
	  	//TODO ft_getenv needed Load the terminal entry 
		printf("reset test 01\n");
	  	return;  // Error handling or fallback
    }
    char *reset_cmd = tgetstr("rs1", NULL);  // Fetch the reset command, if available
    if (reset_cmd)
		printf("reset test 0\n");
	if (reset_cmd) {
        tputs(reset_cmd, 30, ft_putchar);  // Execute the reset command
			printf("reset test\n");
    }
}*/

/*
@glance			initate signals prior readline()
@ft_memset		set signas struct memory to '\0', avoid garbadge
@sa.sa			point signal handler function
@sa.sa_flags	pause everithing when signal recieived and restart after
@sigemptyset	takes an empty list on signals, no additional signals can 
				interfere handler.
@if	SIGINT		in case SIGINT signal received, do what is instructed 
				in sa struct. check sigaction call failure, 
				ignore signal in interactive mode.
@SIG_IGN		reassign the handler for SIGQUIT ctrl-\ to SIG_IGN. Changing sa 
				afterward and applying it to SIGQUIT configures SIGQUIT 
				independently of SIGINT.
@if SIGQUIT		in case SIGQUIT signal received,
				check sigaction call failure, ignore signal in interactive mode
*/

void	init_signals(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Sigaction failed SIGINT");
		exit(EXIT_FAILURE);
    }
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Failed to ignore SIGQUIT");
		exit(EXIT_FAILURE);
	}
}

/*
@glance				prepare Minishell for the next readline() call, 
					act upon SIGINT. readline() handles SIGINT internally, 
					so need to manage the promt with rl_() functions. 
@global variable	to differenciate promt line cleanup ie rl_redisplay 
					is coditional for interactive shell mode only.
@rl_replace_line	clear current input line.
@rl_on_new_line		tell readline() I am on a new line.
@rl_redisplay		request readline to redisplay the prompt.
@write				not fail protected, signal handler speed 
					and atomic-ness overweighs that.
*/

void	sigint_handler(int signum)
{
		if (g_child_pid > 0)
		{
			if (g_child_pid != 2147483647)// I need more info inside the handler
				write(STDOUT_FILENO, "\n", 1);//not needed in case of heredoc
//		printf("child entered handler with pid %d\n", global_child_pid);
		}
		else
		{
			rl_replace_line("", 0);
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
//			printf("parent entered handler with pid %d\n", global_parent_pid);
		}
//		printf("no coditions, just passing signal handler\n");
}
