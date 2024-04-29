#include "cub3d.h"

static int	is_texture_row(char *row, int i)
{
	if (row[i] == 'N' && row[i + 1] == 'O')
		return (1);
	else if (row[i] == 'S' && row[i + 1] == 'O')
		return (1);
	else if (row[i] == 'E' && row[i + 1] == 'A')
		return (1);
	else if (row[i] == 'W' && row[i + 1] == 'E')
		return (1);
	else
		return (0);
}

void	check_file_extension(t_scene *sc, char *path)
{
	int	i;

	i = 0;
	while (path[i] != '.' && path[i])
		i++;
	if (path[i] == '.')
	{
		if (path[i + 1] == 'c' && path[i + 2] == 'u' && path[i + 3] == 'b')
		{
			if (path[i + 4] != '\0' && path[i + 4] != ' ')
				free_invalid_map(sc, 'm');
		}
		else
			free_invalid_map(sc, 'm');
	}
	else
		free_invalid_map(sc, 'm');
}

void	read_config_lines(t_scene *sc, char **row, int *lines)
{
	int	i;

	i = 0;
	while ((*row)[i] == ' ' || (*row)[i] == '\t')
		i++;
	if ((*row)[i] == 'F' || (*row)[i] == 'C')
	{
		init_floor_ceiling_colors(sc, *row, i);
		(*lines)++;
	}
	else if (is_texture_row(*row, i))
	{
		sc->text_init = 1;
		init_texture(sc, *row, i);
		(*lines)++;
	}
	else if (*lines < 6)
		free_wrong_key(sc, *row);
}

void	skip_config_lines(char **row, int *fd)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		*row = get_next_line(*fd);
		skip_empty_lines(row, fd);
		if (*row)
		{
			free(*row);
			i++;
		}
	}
}
