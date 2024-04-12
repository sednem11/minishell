/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by macampos          #+#    #+#             */
/*   Updated: 2024/04/11 18:44:11 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return(1);
	t_main	main;
	char	*user_input;
	char	**cmds;
	int		i;

	i = -1;
	(void)argv;
	(void)main;
	while (1)
	{
		user_input = readline("minishell> ");
		if(!user_input)	
			return 1;
		cmds = ft_split(user_input, ' ');
		add_history(user_input);
		if (cmds[0])
			execute_function(cmds, envp);
	}
}