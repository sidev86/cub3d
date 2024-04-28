#include "cub3d.h"

int	no_value(char *row, int i)
{
	int	value;

	value = 0;
	while (row[i] == ' ' || row[i] == '\t' || row[i] == '-')
		i++;
	while (row[i] != ',')
	{
		if (row[i] >= '0' && row[i] <= '9')
			value = 1;
		i--;
	}
	if (!value)
		return (1);
	return (0);
}

int	missing_commas(char *row)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (row[i] != '\n')
	{
		if (row[i] == ',')
			commas++;
		i++;
	}
	if (commas < 2)
		return (1);
	return (0);
}

void	skip_empty_lines(char **row, int *fd)
{
	while (empty_line(*row))
	{
		free(*row);
		*row = get_next_line(*fd);
	}
}

void	print_map(t_scene *sc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sc->map->map_x)
	{
		j = 0;
		while (j < sc->map->map_y)
		{
			printf("%c", sc->map->room[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
