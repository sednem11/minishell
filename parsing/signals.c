/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:11 by macampos          #+#    #+#             */
/*   Updated: 2024/10/07 10:49:52 by macampos         ###   ########.fr       */
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

void	ctrlc_signal3(int signal, t_main **buf, t_cmd **buf2)
{
	static t_cmd	*something2 = NULL;
	static t_main	*somethign = NULL;
	int				i;

	i = 0;
	if (!somethign)
		if (buf)
			somethign = *buf;
	if (!something2)
		if (buf2)
			something2 = *buf2;
	if (signal == SIGINT)
	{
		signal_received = 1;
		printf("\n");
		rl_replace_line("", 0);
		free_both(somethign);
		free_every_thing(something2, somethign, somethign->check);
		while (i < FOPEN_MAX)
			close(i++);
		somethign = NULL;
		something2 = NULL;
		exit(0);
	}
}

void	signal_main3(t_main *main, t_cmd *cmd, int file)
{
	(void)cmd;
	(void)file;
	ctrlc_signal3(-1, &main, &cmd);
	signal(SIGINT, (void *)ctrlc_signal3);
}
