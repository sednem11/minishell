/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/11/06 13:18:11 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/fs.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int				*redirection;
	int				*valid_arg_for_redirection;
	int				*redirectionpos;
	int				redirectionoverall;
	char			*path;
	char			**args;
	char			**argv2;
	char			**realarg;
	int				*spaces;
	int				fd[2];
	int				numb;
	int				i;
	int				j;
	struct s_cmd	*next;
	struct s_cmd	*begining;
	int				check;
}					t_cmd;

typedef struct s_main
{
	int				*check;
	char			*user_input;
	char			**env;
	char			**export;
	int				status;
	int				spaces;
	struct s_main	*next;
	int				i;
	int				n;
	int				z;
	int				a;
	int				c;
	pid_t			*pid;
	t_cmd			**cmd;
}					t_main;

typedef struct s_path
{
	char			**paths;
	char			*part_path;
	char			*path;
	int				i;
}					t_path;

typedef struct s_split
{
	int				word_len;
	int				ctd;
	int				ctd2;
}					t_split;

typedef struct s_split2
{
	int		i;
	int		k;
	int		j;
	int		flag;
	char	**ptr;
}			t_split2;

typedef struct s_ar
{
	int				i;
	int				j;
	int				flag;
}					t_ar;

typedef struct s_aspas
{
	int	i;
	int	j;
	int	check;
	int	check2;
}		t_aspas;

typedef struct s_expansion
{
	int		i;
	int		k;
}			t_expansion;

int					check_priority_arg(t_cmd *cmd);
void				get_expansion3(char **new, char **expansion, int k, int j);
void				check_args(char *user_input, t_ar *ar, char *argv);
t_cmd				*set_comands(char *argv, t_cmd *cmd, t_main *main);
int					check_args2(char *user_input);
void				check_for_expansion(t_cmd *cmd, char **fakeargs,
						t_main *main);
t_cmd				*set_comands_help(int i, t_cmd *cmd2, t_cmd *begin,
						t_main *main);
int					check_aspas2(char *user_input, int k);
int					check_dolar(char *user_input);
void				free_both(t_main *main);
int					print_export_help2(t_main *main, int i, int n, int z);
void				redirection3_help(t_cmd *cmd, int i, int file, char *input);
void				not_builtin_helper(int *check, char **envp, t_cmd *cmd,
						t_main *main);
void				child2(t_cmd *cmd, t_main *main);
int					check_equal(char *value);
void				print_dolar(t_main *main, char *arg);
int					count_dif_redirections(char **argv);
char				*word_aloc3(char const *str, char c);
void				closepipes(t_cmd *cmd);
void				free_paths(char **paths, char **cmd);
char				*get_paths(char *argv, char **envp);
int					last_reversed(t_cmd *cmd, int flag);
void				aplly_redirections(t_cmd *cmd, t_main *main);
void				closeallpipes(t_cmd *cmd);
char				**ft_split3(char const *s, char c);
void				free_every_thing(t_cmd *cmd, t_main *main, int *check);
void				redirection3(t_cmd *cmd, int i, int file, t_main *main);
void				redirection4(t_cmd *cmd, int i, int file, t_main *main);
void				alloc_heredoc(t_cmd *cmd, char *alocated);
int					check_last_redirection(t_cmd *cmd, int i);
int					check_last_redirection2(t_cmd *cmd, int i);
void				redirection2(t_cmd *cmd, int i, int file, t_main *main);
void				redirection_1(t_cmd *cmd, int file, int i, t_main *main);
int					count_redirections(char **argv);
void				free_cmd_args(t_cmd *cmd);
char				**ft_split2(char const *s, char c, t_split2 *spl2);
void				closepipes(t_cmd *cmd);
void				set_comands2(t_cmd *cmd, t_main *main, char **path2,
						char **envp);
t_main				*execute_function(char *user_input, char **envp, t_cmd *cmd,
						t_main *main);
int					pars_args(char **cmds);
t_main				*check_builtins(t_cmd *cmd, char **envp, t_main *main,
						char *user_input);
void				cd(t_cmd *cmd, char **envp, t_main *main);
void				echo(t_cmd *cmd, t_main *main, int i, char *user_input);
void				env(t_cmd *cmd, char **envp);
t_main				*exitt(t_cmd *cmd, char **envp, t_main *main);
t_main				*export(t_cmd *cmd, char **envp, t_main *main);
void				pwd(t_cmd *cmd, char **envp, t_main *main);
t_main				*unset(t_cmd *cmd, t_main *main, char **envp);
t_cmd				*initiate_args(char *user_input, char **envp, t_cmd *cmd,
						t_main *main);
char				*get_paths(char *argv, char **envp);
int					check_pipes(char *user_input);
void				print_env(char **envp);
int					check_builtins2(t_cmd *cmd, char **envp, t_main *main);
int					matrixlen(char **envp);
void				free_env_and_export(t_main *main);
t_main				*set_main2(t_main *main, char **envp, char **envp2,
						char *exported);
int					*check_paired(char *exported, char **envp, char **envp2,
						int len);
int					ft_strlen_upd(char *str);
int					find_equal(char *arg);
void				print_export(t_main *main);
t_main				*set_main3(t_main *main, char **envp, char **envp2,
						char *exported);
t_main				*set_main(t_main *main, char **envp);
void				signal_main(void);
void				signal_main2(void);
void				check_redirections(t_cmd *cmd, char *arg, int j);
char				**initialize_pathss(char *argv, t_cmd **cmd2);
int					check_cmds(t_main *main);
void				closepipes_helper(t_cmd *cmd);
void				process_heredoc3(t_cmd *cmd, int i, int file, char *input);
void				open_file2(t_cmd *cmd, int i, int *file, t_main *main);
void				signal_main3(t_main *main, t_cmd *cmd, int file);
void				ctrl_slash(int signal);
void				ctrlc_signal2(int signal);
int					check_aspas(char *user_input, int k, t_aspas *asp);
int					arg_len(char **args);
char				**ft_split4(char const *s, char c, char c2);
int					ft_strlen_updated(char *line);
int					check_overall_args(t_cmd *cmd);
char				*word_aloc4(char const *str, char c, char c2);
int					check_builtins3(t_cmd *cmd, char **envp, t_main *main);
int					*check_paired2(char *exported, char **envp, char **envp2,
						int len);
void				not_builtin_helper(int *check, char **envp, t_cmd *cmd,
						t_main *main);
int					check_backward_redirection(t_cmd *cmd);
int					check_dolar(char *user_input);
void				free_value(char **value);
void				ctrlc_signal(int signal);
void				ctrlc_signal2(int signal);
void				echo_redirections3(t_cmd *cmd);
void				set_main2_help2(t_main *mainn, int *place, char **envp,
						char *exported);
int					check_args2_help(char *user_input, int i);
int					check_args2_help2(char *user_input, int i, int j);
void				set_comands_help3(t_cmd *cmd2, char *argv, t_cmd *cmd,
						char **path2);
int					aspas_help(char *user_input, int k, t_aspas *asp);
void				redirection3_help2(t_cmd *cmd, int i, int file);
void				redirection2_help(t_cmd *cmd, int i, int file,
						t_main *main);
t_cmd				*initiate_args2(char *argv, t_ar *ar, t_cmd *cmd,
						t_main *main);

#endif