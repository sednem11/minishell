/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:02:33 by macampos          #+#    #+#             */
/*   Updated: 2024/11/05 17:46:34 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	alloc_heredoc(t_cmd *cmd, char *alocated)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), matrixlen(cmd->realarg) + 2);
	while (cmd->realarg[i])
	{
		new[i] = cmd->realarg[i];
		i++;
	}
	if (alocated)
		new[i] = ft_strdup(alocated);
	free(cmd->realarg);
	cmd->realarg = new;
}

void	process_heredoc3(t_cmd *cmd, int i, int file, char *input)
{
	while (input && (strcmp(input, &cmd->args[cmd->redirectionpos[i]][2]) != 0
		|| ft_strlen(input) != ft_strlen(&cmd->args[cmd->redirectionpos[i]]
			[2])))
	{
		if (strcmp(input, &cmd->args[cmd->redirectionpos[i]][2]) != 0
			&& ft_strlen(input) != ft_strlen(&cmd->args[cmd->redirectionpos[i]]
				[2]))
		{
			write(file, input, ft_strlen(input));
			write(file, "\n", 1);
		}
		input = readline("heredoc> ");
	}
}

void	open_file2(t_cmd *cmd, int i, int *file, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
		*file = (open(&cmd->args[cmd->redirectionpos[i]][1], O_RDONLY, 0777));
	else
		*file = (open(cmd->args[cmd->redirectionpos[i] + 1], O_RDONLY, 0777));
	if (*file == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		closepipes(cmd);
		free_both(main);
		free_every_thing(cmd, main, main->check);
		exit(127);
	}
}

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if ((ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		|| (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& ft_strlen(cmd->args[0]) == 6) || (ft_strncmp(cmd->args[0], "pwd",
				3) == 0 && ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "env", 3) == 0
			&& ft_strlen(cmd->args[0]) == 3) || (ft_strncmp(cmd->args[0],
				"exit", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		|| (ft_strncmp(cmd->args[0], "echo", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4) || (ft_strncmp(cmd->args[0],
				"unset", 5) == 0 && ft_strlen(cmd->args[0]) == 5))
		return (0);
	else
		return (1);
}

int	check_builtins3(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0],
			"export", 6) == 0 || ft_strncmp(cmd->args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->args[0], "env", 3) == 0 || ft_strncmp(cmd->args[0],
			"exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (0);
	else
		return (1);
}
