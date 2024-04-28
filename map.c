#include "cub3d.h"

int	count_map_cols(char *r)
{
	int	i;
	int	cols;

	i = 0;
	cols = 0;
	while (r[i] != '\0' && r[i] != '\n')
	{
		while (r[i] == '\t')
			i++;
		if (r[i] == '0' || r[i] == '1' || r[i] == 'N' || r[i] == 'S'
			|| r[i] == 'E' || r[i] == 'W' || r[i] == ' ')
			cols++;
		i++;
	}
	return (cols);
}

void	save_map_row_values(t_scene *sc, char *row, int x)
{
	int	y;
	int	cols;

	y = 0;
	cols = count_map_cols(row);
	while (y < cols)
	{
		while (row[y] == '\t')
			y++;
		if (row[y] == '0')
			sc->map->room[x][y] = '0';
		else if (row[y] == '1')
			sc->map->room[x][y] = '1';
		else if (row[y] == ' ')
			sc->map->room[x][y] = '1';
		else if (row[y] == 'N' || row[y] == 'S' || row[y] == 'W'
			|| row[y] == 'E')
		{
			sc->map->room[x][y] = row[y];
			put_player_on_map(sc, row[y], x, y);
		}
		y++;
	}
	while (y < sc->map->cols)
		sc->map->room[x][y++] = '2';
}

void	read_map_for_init(t_scene *sc, char **row, int *fd)
{
	while (*fd != -1)
	{
		*row = get_next_line(*fd);
		while (empty_line(*row))
		{
			free(*row);
			*row = get_next_line(*fd);
		}
		if (!(*row) && !sc->map->map_present)
			free_missing_map(sc, *row);
		if (*row)
		{
			sc->map->map_present = 1;
			sc->map->rows++;
		}
		else
			break ;
		if (count_map_cols(*row) > sc->map->cols)
			sc->map->cols = count_map_cols(*row);
		free(*row);
	}
}

void	check_row_validity(t_scene *sc, char *row)
{
	int	i;

	i = 0;
	while (row[i] != '\n' && row[i])
	{
		if (row[i] != '1' && row[i] != '0' && row[i] != ' ' && row[i] != '\t'
			&& row[i] != 'N' && row[i] != 'S' && row[i] != 'W' && row[i] != 'E')
		{
			free_map_wrong(sc, row);
		}
		i++;
	}
}

void	read_map(t_scene *sc, char *path)
{
	int		fd;
	int		num_row;
	char	*row;

	num_row = 0;
	fd = open(path, O_RDONLY);
	skip_config_lines(&row, &fd);
	//skip_empty_lines(&row, &fd);
	while (fd != -1)
	{
		row = get_next_line(fd);
		skip_empty_lines(&row, &fd);
		if (row)
		{
			check_row_validity(sc, row);
			save_map_row_values(sc, row, num_row);
		}
		else
			break ;
		num_row++;
		free(row);
	}
}
