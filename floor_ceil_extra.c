/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:54:47 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:54:49 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	digits_between_space(char *row, int j)
{
	j++;
	while (row[j] != ',' && row[j] != '\n')
	{
		if (row[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	count_the_digits(t_scene *sc, char *row, int *i)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (row[j] != ',' && row[j] != '\n' && row[j] != '\0')
	{
		if (row[j] != ' ' && row[j] != '\t')
		{
			count++;
			if (row[j] < '0' || row[j] > '9')
				free_doublerow_ceilfloor(sc, row, 'v');
		}
		if (row[j] == ' ' && count > 0 && digits_between_space(row, j))
			free_doublerow_ceilfloor(sc, row, 'v');
		j++;
	}
	return (count);
}
