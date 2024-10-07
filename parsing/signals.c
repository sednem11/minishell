/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:11 by macampos          #+#    #+#             */
/*   Updated: 2024/10/07 10:03:47 by macampos         ###   ########.fr       */
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

volatile sig_atomic_t	signal_received = 0;

void	ctrlc_signal3(int signal)
{
	if (signal == SIGINT)
	{
		signal_received = 1;
		printf("\n");
		rl_replace_line("", 0);
		exit(0);
	}
}

sig_atomic_t	check_signal_received2(void)
{
	return (signal_received);
}

int	check_signal_received(t_main *main, t_cmd *cmd, int file)
{
	if (signal_received == 1)
	{
		closeallpipes(cmd);
		close(file);
		free_both(main);
		free_every_thing(cmd, main, main->check);
		return(0);
	}
	return(1);
}

void	signal_main3(t_main *main, t_cmd *cmd, int file)
{
	(void)main;
	(void)cmd;
	(void)file;
	signal(SIGINT, ctrlc_signal3);
}
