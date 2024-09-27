/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:28 by macampos          #+#    #+#             */
/*   Updated: 2024/09/27 17:46:06 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_cmd *cmd, char **envp, t_main *main)
{
	char	*cwd;

	(void)envp;
	(void)cmd;
	cwd = getcwd(0, 0);
	if (!cwd)
		return ((void)printf("fuckoff\n"));
	printf("%s\n", cwd);
	main->status = 0;
}
