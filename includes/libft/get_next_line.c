/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:39:51 by macampos          #+#    #+#             */
/*   Updated: 2023/12/05 17:15:35 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		ft_clearbuf(buffer);
		return (NULL);
	}
	while (*buffer != '\0' || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin2(line, buffer);
		if (ft_checknl(buffer))
			break ;
	}
	return (line);
}
