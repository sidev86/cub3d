/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:55:43 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:55:44 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_get_stock_len(char *stock)
{
	int	i;

	i = 0;
	if (f_strchr(stock, '\n') == NULL)
		return (ft_strlen(stock));
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i + 1);
}

char	*ft_get_line(char *stock)
{
	char	*line;
	int		i;
	int		len;

	line = NULL;
	len = ft_get_stock_len(stock);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && i < len)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_get_spare(char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i] != '\n')
		i++;
	i = i + 1;
	j = 0;
	while (i < BUFFER_SIZE)
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}

char	*ft_line_results(int ret, char *stock, char *buf)
{
	char		*line;

	line = NULL;
	if (ft_strlen(stock) == 0)
	{
		free(stock);
		return (NULL);
	}
	line = ft_get_line(stock);
	if (ret > 0)
		ft_get_spare(buf);
	free(stock);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*stock;
	int			ret;

	stock = NULL;
	if ((read(fd, buf, 0) == -1) || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	stock = f_strjoin(stock, buf);
	while (f_strchr(stock, '\n') == NULL && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(stock);
			return (NULL);
		}
		buf[ret] = '\0';
		stock = f_strjoin(stock, buf);
	}
	return (ft_line_results(ret, stock, buf));
}
