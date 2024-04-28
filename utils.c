#include "cub3d.h"

int	close_window(void *param)
{
	t_scene	*s;
	int		i;

	s = (t_scene *)param;
	i = 0;
	while (i < s->map->rows)
		free(s->map->room[i++]);
	free(s->map->room);
	s->map->room = NULL;
	i = 0;
	while (i < 8)
	{
		free(s->texture[i]);
		i++;
	}
	free(s->map);
	free(s->cam);
	free(s->player);
	free(s->texture);
	free(s->ray);
	mlx_destroy_image(s->mlx, s->img.img);
	mlx_destroy_window(s->mlx, s->win);
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	exit(0);
}

int	empty_line(char *row)
{
	int	i;

	i = 0;
	if (!row)
		return (0);
	while (row[i] == ' ' || row[i] == '\t')
		i++;
	if (row[i] == '\n')
		return (1);
	else
		return (0);
}

void	clear_buffer(t_scene *sc)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < W_HEIGHT)
	{
		y = 0;
		while (y < W_WIDTH)
		{
			sc->buff[x][y] = 0;
			y++;
		}
		x++;
	}
}

int	get_len(char *row, int i)
{
	int	len;

	len = 0;
	while (row[i] != ' ' && row[i] != '\t' && row[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}
