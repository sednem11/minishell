/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:13:45 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 15:40:06 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redirections(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if ((ft_strncmp(argv[i], ">", 1) == 0) || (ft_strncmp(argv[i], "<",
					1) == 0) || (ft_strncmp(argv[i], "<<", 2) == 0)
			|| (ft_strncmp(argv[i], ">>", 2) == 0))
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	return (j);
}

void	closeallpipes(t_cmd *cmd)
{
	while (cmd)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd = cmd->next;
	}
}

void	free_cmd_args2(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	i = 0;
	while (cmd->realarg[i])
	{
		free(cmd->realarg[i]);
		i++;
	}
	i = 0;
	while (cmd->argv2[i])
	{
		free(cmd->argv2[i]);
		i++;
	}
}

void	free_cmd_args(t_cmd *cmd)
{
	t_cmd	*temporary;

	closeallpipes(cmd->begining);
	temporary = cmd->begining;
	while (temporary)
	{
		cmd = temporary;
		free_cmd_args2(cmd);
		free(cmd->argv2);
		free(cmd->realarg);
		free(cmd->valid_arg_for_redirection);
		temporary = cmd->next;
		free(cmd->redirection);
		free(cmd->redirectionpos);
		free(cmd->path);
		free(cmd);
	}
}

char	**initialize_pathss(char *argv, t_cmd **cmd2)
{
	char	**path2;
	char	*temp;

	path2 = ft_calloc(sizeof(char *), 2);
	path2[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	temp = path2[0];
	path2[0] = ft_strjoin(path2[0], "/usr/sbin:/usr/bin:/sbin:/bin");
	free(temp);
	*cmd2 = ft_calloc(1, sizeof(t_cmd));
	(*cmd2)->argv2 = ft_split(argv, '\4');
	return (path2);
}
