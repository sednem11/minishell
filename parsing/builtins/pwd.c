/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:28 by macampos          #+#    #+#             */
/*   Updated: 2024/09/09 15:59:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_cmd *cmd, char **envp)
{
	char	*cwd;

	(void)envp;
	(void)cmd;
	cwd = getcwd(0, 0);
	if (!cwd)
		return ((void)printf("fuckoff\n"));
	printf("%s\n", cwd);
}
