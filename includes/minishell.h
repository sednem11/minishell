/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/04/22 21:33:14 by macampos         ###   ########.fr       */
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
	char			*prompt;
	char			**env;
	struct s_main	*next;
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
	struct s_main	*main;
}	t_cmd;

void	set_comands2(t_cmd *cmd, int i);
t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd, t_main *main);
int		pars_args(char **cmds);
t_main 	*check_builtins(t_cmd *cmd, char **envp, t_main *main);
void	cd(t_cmd *cmd, char **envp);
void	echo(t_cmd *cmd, int i);
void	env(t_cmd *cmd, char **envp);
void	exitt(t_cmd *cmd, char **envp);
t_main	*export(t_cmd *cmd, char **envp, t_main *main);
void	pwd(t_cmd *cmd, char **envp);
void	unset(t_cmd *cmd, char **envp);
t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd);
char	*get_paths(char *argv, char **envp);
int		check_pipes(char *user_input);
void	print_env(char **envp);
int		check_builtins2(t_cmd *cmd, char **envp, t_main *main);
int 	matrixlen(char **envp);
t_main	*free_env(t_main *main);

#endif