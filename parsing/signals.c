/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:11 by macampos          #+#    #+#             */
/*   Updated: 2024/09/06 11:54:12 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_signal2(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ctrlc_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


void	ctrl_slash(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("Quit\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_main(void)
{
	signal(SIGINT, ctrlc_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_main2(void)
{
	signal(SIGINT, ctrlc_signal2);
	signal(SIGQUIT, ctrl_slash);
}

volatile sig_atomic_t signal_received = 0;

void	ctrlc_signal3(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal_received = 1;
		// printf("two %i\n", signal_received);
	}
}

int		check_signal_received(void)
{
	return(signal_received);
}

void	signal_main3(t_main *main, t_cmd *cmd, int file)
{
	// int *check;

	// check = NULL;
	(void)main;
	(void)cmd;
	(void)file;
	printf("one %i\n", signal_received);
	if (signal_received == 1)
	{
		// close(file);
		// free_both(main);
		// free_env_and_export(main);
		// free_every_thing(cmd, main, check);
		exit(0);
	}
	signal(SIGINT, ctrlc_signal3);
	printf(" three %i\n", signal_received);
}
