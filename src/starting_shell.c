/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/09/04 17:45:43 by macampos         ###   ########.fr       */
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
		exit(1);
	}
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	char	*b;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal_main2();
	main->check = check_paired("PATH=", main->env, main->export, 5);
	b = NULL;
	child2(cmd, main);
	closeallpipes(cmd);
	free_both(main);
	if (check_builtins2(cmd, envp, main) == 1 && main->check[0] == -1)
	{
		execve(b, cmd->realarg, envp);
		write(2, " No such file or directory\n", 28);
		exit(1);
	}
	if (check_builtins2(cmd, envp, main) == 1 && main->check[0] != -1)
		not_builtin(main->check, envp, cmd, main);
	free(main->check);
	main->check = NULL;
	main = check_builtins(cmd, envp, main, user_input);
	free_every_thing(cmd, main, main->check);
	exit(0);
}

t_cmd	*execute_function_helper(t_main *main, int i, t_cmd *cmd,
		char *user_input)
{
	signal(SIGINT, ctrlc_signal2);
	signal(SIGQUIT, SIG_DFL);
	main->cmd[i] = cmd;
	main->pid[i] = fork();
	if (main->pid[i] == 0)
		child_process(user_input, main->env, cmd, main);
	if (cmd->redirectionoverall == 2)
	{
		
		while (waitpid(main->pid[i], &main->status, 0) != -1)
			;
	}
	closepipes(cmd);
	cmd = cmd->next;
	return (cmd);
}

t_main	*execute_cmd(t_cmd *cmd, char **envp, t_main *main, char *user_input)
{
	int	i;

	i = 0;
	if (cmd->next || check_builtins2(cmd, envp, main) == 1
		|| cmd->redirectionoverall != 0)
	{
		main->cmd = ft_calloc(10000, sizeof(t_cmd));
		main->pid = ft_calloc(10000, sizeof(pid_t));
		while (cmd)
		{
			closepipes_helper(cmd);
			cmd = execute_function_helper(main, i++, cmd, user_input);
		}
	}
	else
		main = check_builtins(cmd, envp, main, user_input);
	return (main);
}

// void	kill_process(t_main *main, int i)
// {
// 	if (getchar() == 10)
// 		kill(main->pid[i], SIGUSR1);
// 	else
// 		kill_process(main, i);
// }

t_main	*execute_function(char *user_input, char **envp,
	t_cmd *cmd, t_main *main)
{
	int	i;

	main = execute_cmd(cmd, envp, main, user_input);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal_main2();
	i = 0;
	if (main->pid)
	{
		while (main->pid[i])
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			signal_main2();
			// if (check_cmds(main) == 1 && !ft_strncmp(main->cmd[i]->args[0],
			// 		"cat", 3) && !main->cmd[i]->args[1])
			// 	kill_process(main, i);
			waitpid(main->pid[i], &main->status, 0);
			if (WIFEXITED(main->status))
				main->status = WEXITSTATUS(main->status);
			i++;
		}
		free(main->pid);
		main->pid = NULL;
	}
	if (main->cmd)
	{
		free(main->cmd);
		main->cmd = NULL;
	}
	return (main);
}
