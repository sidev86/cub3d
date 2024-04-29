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

void	texture_to_draw(t_scene *sc, int x)
{
	int		y;

	y = sc->ray->draw_start;
	while (y < sc->ray->draw_end)
	{
		sc->tex_y = (int)sc->tex_pos & (T_HEIGHT - 1);
		sc->tex_pos += sc->step;
		if (sc->ray->side == 0 && sc->map->map_x >= sc->player->pos_x)
			sc->color = sc->texture[0][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 0 && sc->map->map_x < sc->player->pos_x)
			sc->color = sc->texture[1][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 1 && sc->map->map_y >= sc->player->pos_y)
			sc->color = sc->texture[2][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 1 && sc->map->map_y < sc->player->pos_y)
			sc->color = sc->texture[3][T_HEIGHT * sc->tex_y + sc->tex_x];
		if (sc->ray->side == 1)
			sc->color = (sc->color >> 1) & 8355711;
		sc->buff[y][x] = sc->color;
		sc->re_buf = 1;
		y++;
	}
}
