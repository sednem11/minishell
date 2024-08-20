/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/08/20 16:43:23 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_builtin(int *check, char **envp, t_cmd *cmd, t_main *main)
{
	char	**a;

	a = NULL;
	if (ft_strncmp(cmd->args[0], "./minishell", 11) != 0)
		not_builtin_helper(check, envp, cmd, main);
	else
	{
		execve("./minishell", a, envp);
		printf("%s\n", strerror(errno));
	}
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	char	*b;
	int		*check;

	check = check_paired("PATH=", main->env, main->export, 5);
	b = NULL;
	child2(cmd, main);
	check_nobuiltins_notexecutable(check, cmd, main);
	if (check_builtins2(cmd, envp, main) == 1 && check[0] == -1)
	{
		execve(b, cmd->realarg, envp);
		write(2, " No such file or directory\n", 28);
	}
	if (check_builtins2(cmd, envp, main) == 1 && check[0] != -1)
		not_builtin(check, envp, cmd, main);
	check_builtins(cmd, envp, main, user_input);
	free_every_thing(cmd, main, check);
	exit(0);
}

void	closepipes_helper(t_cmd *cmd)
{
	if ((cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
		|| (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset", 5) == 0)
		|| (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit", 4) == 0))
		closepipes(cmd);
}

t_cmd	*execute_function_helper(t_main *main, char **envp, t_cmd *cmd,
		char *user_input)
{
	pid_t	id;

	id = fork();
	if (id == 0)
		child_process(user_input, envp, cmd, main);
	if (cmd->redirectionoverall == 2)
	{
		while (waitpid(id, &main->status, 0) != -1)
			;
	}
	closepipes(cmd);
	cmd = cmd->next;
	return (cmd);
}

t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd,
		t_main *main)
{
	if (cmd->next || check_builtins2(cmd, envp, main) == 1
		|| cmd->redirectionoverall != 0)
	{
		while (cmd)
		{
			closepipes_helper(cmd);
			if (cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
				return (export(cmd, envp, main));
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset",
					5) == 0)
				return (unset(cmd, main, envp));
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit",
					4) == 0)
				return (exitt(cmd, envp, main));
			cmd = execute_function_helper(main, envp, cmd, user_input);
		}
	}
	else
		main = check_builtins(cmd, envp, main, user_input);
	while (waitpid(-1, &main->status, 0) != -1)
		;
	if (WIFEXITED(main->status))
		main->status = WEXITSTATUS(main->status);
	return (main);
}
