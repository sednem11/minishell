/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/04/10 14:27:31 by macampos         ###   ########.fr       */
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

#endif