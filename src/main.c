/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by macampos          #+#    #+#             */
/*   Updated: 2024/04/17 23:49:25 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return(1);
	t_cmd	*cmd;
	char	*user_input;

	cmd = NULL;
	(void)argv;
	while (1)
	{
		user_input = readline("minishell> ");
		if(!user_input)	
			return 1;
		cmd = initiate_args(user_input, envp, cmd);
		if (user_input)
			add_history(user_input);
		if (user_input)
			execute_function(user_input, envp, cmd);
	}
}
