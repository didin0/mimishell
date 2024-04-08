/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsainas <rsainas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:32:00 by rsainas           #+#    #+#             */
/*   Updated: 2024/04/08 18:35:11 by rsainas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

/*
@glance			initate signals prior readline()
@ft_memset		set signas struct memory to '\0', avoid garbadge
@sa->sa			point signal handler function
@sa->sa_flags	pause everithing when signal recieived and restart after
@sigemptyset	takes an empty list on signals, all signals can interfere
				handler.
@sigaddset		in this empty set start listening for SIGINT
@if	SIGINT		in case SIGINT signal received, do what is instructed 
				in sa struct. check sigaction call failure, 
				ignore signal in interactive mode.
@SIG_IGN		reassign the handler for SIGQUIT to SIG_IGN. Changing sa 
				afterward and applying it to SIGQUIT configures SIGQUIT 
				independently of SIGINT.
@if SIGQUIT		in case SIGQUIT signal received,
				check sigaction call failure, ignore signal in interactive mode
*/

void	init_signals()
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
@global variable	in non-interactive mode the shell sends SIGINT only to
					foreground processes. Use global variable to get child pid 
					and send SIGINT to child process (kill). 
					Also to differenciate promt line cleanup ie rl_redisplay 
					is coditional for interactive shell mode only.
@kill				terminate the child process.
@rl_replace_line	clear current input line.
@rl_on_new_line		tell readline() I am on a new line.
@rl_redisplay		request readline to redisplay the prompt.
@global variable	in non-interactive mode the shell sends SIGINT only to
					foreground processes. Use global variable to get child pid 
					and send SIGINT to child process (kill). 
					Also to differenciate promt line cleanup ie rl_redisplay 
					is coditional for interactive shell mode only.
@write				not fail protected, signal handler speed overweighs that.
*/

void	sigint_handler(int signum)
{
//	reset_terminal();
	if (signum == SIGINT)
	{
		if (global_child_pid > 0)
		{
			kill(global_child_pid, SIGINT);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			rl_replace_line("", 0);
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
//	fflush(stdout);
//	reset_terminal();
}
