#include "cub3d.h"

static unsigned int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	init_rgbstr(char *rgb)
{
	int	j;

	j = 0;
	while (j < 3)
		rgb[j++] = 0;
}

static void	get_rgb_digits(t_scene *sc, char *row, char *rgb_str, int *i)
{
	int	j;
	int	count;

	j = 0;
	while (row[*i] == ' ' || row[*i] == '\t')
		(*i)++;
	count = count_the_digits(sc, row, i);
	printf("count: %d\n", count);
	if (count > 3)
		free_doublerow_ceilfloor(sc, row, 'v');
	while (row[*i] != ',' && row[*i] != ' ' && row[*i] != '\n' && row[*i] != '\0')
		rgb_str[j++] = row[(*i)++];
	while (row[*i] == ' ' || row[*i] == '\t')
		(*i)++;
	(*i)++;
}

void	get_rgb_values(t_scene *sc, char *row, int i, char type)
{
	int		t;
	char	rgb_str[3];

	t = 0;
	init_rgbstr(rgb_str);
	while (t < 3)
	{
		get_rgb_digits(sc, row, rgb_str, &i);
		if (no_value(row, i) || missing_commas(row))
			free_doublerow_ceilfloor(sc, row, 'm');
		if (type == 'f')
			sc->floor[t] = ft_atoi(rgb_str);
		else if (type == 'c')
			sc->ceil[t] = ft_atoi(rgb_str);
		if (sc->floor[t] < 0 || sc->ceil[t] < 0 || sc->floor[t] > 255
			|| sc->ceil[t] > 255)
			free_doublerow_ceilfloor(sc, row, 'v');
		init_rgbstr(rgb_str);
		t++;
	}
}

void	draw_floor_ceiling(t_scene *sc)
{
	int				x;
	int				y;
	unsigned int	floor_hex;
	unsigned int	ceil_hex;

	x = 0;
	y = 0;
	floor_hex = rgb_to_hex(sc->floor[0], sc->floor[1], sc->floor[2]);
	ceil_hex = rgb_to_hex(sc->ceil[0], sc->ceil[1], sc->ceil[2]);
	while (y < W_HEIGHT)
	{
		while (x < W_WIDTH)
		{
			sc->buff[y][x] = floor_hex;
			sc->buff[W_HEIGHT - y - 1][x] = ceil_hex;
			x++;
		}
		x = 0;
		y++;
	}
}
