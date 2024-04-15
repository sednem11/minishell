/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/04/15 19:06:00 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct  s_main
{
	char	*prompt;
}	t_main;

int	execute_function(char **cmd, char **envp);
int	pars_args(char **cmds);
int check_builtins(char **cmd, char *path, char **envp);
void	cd(char **cmd, char *path, char **envp);
void	echo(char **cmd, char *path, char **envp);
void	env(char **cmd, char *path, char **envp);
void	exitt(char **cmd, char *path, char **envp);
void	export(char **cmd, char *path, char **envp);
void	pwd(char **cmd, char *path, char **envp);
void	unset(char **cmd, char *path, char **envp);

#endif