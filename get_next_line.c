/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:19:33 by sibrahim          #+#    #+#             */
/*   Updated: 2022/11/21 11:37:08 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static void	ft_read_buf(char **str, char *buf, int fd)
{
	int		i;
	char	*tmp;

	if (!ft_strchr(*str, '\n') || !*str)
		i = read(fd, buf, BUFFER_SIZE);
	else
		i = ft_strlen(*str);
	while (i > 0 && !ft_strchr(*str, '\n'))
	{
		buf[i] = 0;
		if (!*str)
			*str = ft_substr(buf, 0, i);
		else
		{
			tmp = *str;
			*str = ft_strjoin(*str, buf);
			free(tmp);
		}
		if (ft_strchr(*str, '\n') || i < BUFFER_SIZE)
			break ;
		i = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
}

static char	*ft_extract_line(char **str)
{
	char	*line;
	char	*tmp;
	int		s_len;
	int		al_bytes;

	line = NULL;
	if (ft_strchr(*str, '\n'))
	{
		s_len = ft_strlen(*str);
		al_bytes = ft_strlen(ft_strchr(*str, '\n'));
		line = ft_substr(*str, 0, s_len - al_bytes + 1);
		tmp = *str;
		*str = ft_substr(*str, s_len - al_bytes + 1, al_bytes - 1);
		free(tmp);
		return (line);
	}
	line = ft_substr(*str, 0, ft_strlen(*str));
	free(*str);
	*str = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;

	buf = malloc(sizeof(*buf) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (fd == -1 || BUFFER_SIZE < 1)
	{
		free(buf);
		return (NULL);
	}
	ft_read_buf(&str, buf, fd);
	if (str && ft_strlen(str) > 0)
		return (ft_extract_line(&str));
	free(str);
	str = 0;
	return (NULL);
}
