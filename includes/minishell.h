/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/04/19 01:01:43 by macampos         ###   ########.fr       */
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

typedef struct	s_main
{
	char	*prompt;
}	t_main;


typedef struct	s_cmd
{
	char			*path;
	char			**args;
	int				fd[2];
	int 			numb;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*begining;
}	t_cmd;

void	set_comands2(t_cmd *cmd, int i);
int		execute_function(char *user_input, char **envp, t_cmd *cmd);
int		pars_args(char **cmds);
int 	check_builtins(t_cmd *cmd, char **envp);
void	cd(t_cmd *cmd, char **envp);
void	echo(t_cmd *cmd, char **envp);
void	env(t_cmd *cmd, char **envp);
void	exitt(t_cmd *cmd, char **envp);
void	export(t_cmd *cmd, char **envp);
void	pwd(t_cmd *cmd, char **envp);
void	unset(t_cmd *cmd, char **envp);
t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd);
char	*get_paths(char *argv, char **envp);
int		check_pipes(char *user_input);

#endif