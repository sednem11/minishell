/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:28 by macampos          #+#    #+#             */
/*   Updated: 2024/04/21 23:04:58 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_cmd *cmd, char **envp)
{
	char	cwd[100];

	(void)envp;
	(void)cmd;
	getcwd(cwd, 100);
	printf("%s\n", cwd);
}