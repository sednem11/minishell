/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/06/20 15:54:36 by macampos         ###   ########.fr       */
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
	char			**env;
	char			**export;
	struct s_main	*next;
}	t_main;


typedef struct	s_cmd
{
	int				*redirection;
	int				*redirectionpos;
	char			*path;
	char			**args;
	char			**argv2;
	char			**realarg;
	int				fd[2];
	int 			numb;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*begining;
	int				check;
}	t_cmd;

int		count_redirections(char **argv);
void	free_cmd_args(t_cmd *cmd);
char	**ft_split2(char const *s, char c);
void	closepipes(t_cmd *cmd);
void	set_comands2(t_cmd *cmd, int i);
t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd, t_main *main);
int		pars_args(char **cmds);
t_main	*check_builtins(t_cmd *cmd, char **envp, t_main *main, char *user_input);
void	cd(t_cmd *cmd, char **envp);
void	echo(t_cmd *cmd, t_main *main, int i, char *user_input);
void	env(t_cmd *cmd, char **envp);
void	exitt(t_cmd *cmd, char **envp, t_main *main);
t_main	*export(t_cmd *cmd, char **envp, t_main *main);
void	pwd(t_cmd *cmd, char **envp);
t_main	*unset(t_cmd *cmd, t_main *main, char **envp);
t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd);
char	*get_paths(char *argv, char **envp);
int		check_pipes(char *user_input);
void	print_env(char **envp);
int		check_builtins2(t_cmd *cmd, char **envp, t_main *main);
int 	matrixlen(char **envp);
void	free_env_and_export(t_main *main);
t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported);
int		*check_paired(char *exported, char **envp, char **envp2, int len);
int		ft_strlen_updated(char *str);
int		find_equal(char *arg);
void	print_export(t_main *main);
t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported);
void	free_every_main(t_main *main);
void	free_every_cmd(t_cmd *cmd);
t_main	*set_main(t_main *main, char **envp);
void	signal_main(void);

#endif