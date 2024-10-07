/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/09/25 14:59:50 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if ((ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		|| (ft_strncmp(cmd->args[0], "export", 6) == 0
			&& ft_strlen(cmd->args[0]) == 6) || (ft_strncmp(cmd->args[0], "pwd",
				3) == 0 && ft_strlen(cmd->args[0]) == 3)
		|| (ft_strncmp(cmd->args[0], "env", 3) == 0
			&& ft_strlen(cmd->args[0]) == 3) || (ft_strncmp(cmd->args[0],
				"exit", 4) == 0 && ft_strlen(cmd->args[0]) == 4)
		|| (ft_strncmp(cmd->args[0], "echo", 4) == 0
			&& ft_strlen(cmd->args[0]) == 4) || (ft_strncmp(cmd->args[0],
				"unset", 5) == 0 && ft_strlen(cmd->args[0]) == 5))
		return (0);
	else
		return (1);
}

int	check_builtins3(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0],
			"export", 6) == 0 || ft_strncmp(cmd->args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->args[0], "env", 3) == 0 || ft_strncmp(cmd->args[0],
			"exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (0);
	else
		return (1);
}

int	check_last(t_main *main)
{
	int	i;
	int	n;
	int	z;

	n = 0;
	i = 0;
	while (main->export[i])
	{
		if (ft_strlen_upd(main->export[i]) > ft_strlen_upd(main->export[n]))
			z = ft_strlen_upd(main->export[n]);
		else
			z = ft_strlen_upd(main->export[i]);
		if (ft_strncmp(main->export[i], main -> export[n], z) > 0)
			n = i;
		i++;
	}
	return (n);
}

int	print_export_help(t_main *main, int i, int n, int z)
{
	if (ft_strlen_upd(main->export[i]) > ft_strlen_upd(main->export[n]))
		z = ft_strlen_upd(main->export[n]);
	else
		z = ft_strlen_upd(main->export[i]);
	return (z);
}

void	print_export(t_main *main)
{
	main->a = 0;
	main->c = 0;
	while (matrixlen(main->export) > main->a + 1)
	{
		main->n = check_last(main);
		main->i = 0;
		while (main->export[main->i])
		{
			main->z = print_export_help(main, main->i, main->n, main->z);
			if (ft_strncmp(main->export[main->i], main -> export[main->n], main
					-> z) < 0 && main->a == 0)
				main->n = main->i;
			else if (main->a > 0 && ft_strncmp(main->export[main->i], main
					-> export[main->c],
					ft_strlen_upd(main->export[main->i])) > 0)
				main->n = print_export_help2(main, main->i, main->n, main->z);
			main->i++;
		}
		printf("declare -x %s\n", main->export[main->n]);
		main->c = main->n;
		main->a++;
	}
}

char	*word_aloc3(char const *str, char c)
{
	char	*word;
	t_split	split;
	int		i;

	i = 0;
	split.ctd = 0;
	split.ctd2 = 0;
	split.word_len = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] != '\5')
			split.word_len++;
		i++;
	}
	word = (char *)malloc(split.word_len + 1);
	while (split.ctd < split.word_len)
	{
		while (str[split.ctd2] == '\5')
			split.ctd2++;
		word[split.ctd] = str[split.ctd2];
		split.ctd2++;
		split.ctd++;
	}
	word[split.ctd] = '\0';
	return (word);
}
