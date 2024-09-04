/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:11 by macampos          #+#    #+#             */
/*   Updated: 2024/09/04 19:46:00 by macampos         ###   ########.fr       */
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

void	ctrlc_signal3(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		kill(getpid(), SIGUSR1);
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

void	signal_main3(t_main *main, t_cmd *cmd, int file)
{
	(void)main;
	(void)cmd;
	(void)file;
	signal(SIGINT, ctrlc_signal2); 
	signal(SIGQUIT, ctrl_slash);
	// if (SIGINT || SIGQUIT)
	// {
	// 	close(file);
	// 	free_both(main);
	// 	free_env_and_export(main);
	// 	free_every_thing(cmd, main, NULL);
	// }
}
