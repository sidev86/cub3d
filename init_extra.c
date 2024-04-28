#include "cub3d.h"

void	init_floor_ceiling_colors(t_scene *sc, char *row, int i)
{
	if (row[i] == 'F' && sc->f == 0)
	{
		sc->f = 1;
		get_rgb_values(sc, row, ++i, 'f');
	}
	else if (row[i] == 'C' && sc->c == 0)
	{
		sc->c = 1;
		get_rgb_values(sc, row, ++i, 'c');
	}
	else
		free_doublerow_ceilfloor(sc, row, 'd');
}

void	set_initial_ray_data(t_scene *sc, int x)
{
	sc->cam->x = 2 * x / (double)W_WIDTH - 1;
	sc->ray->dir_x = sc->player->dir_x + sc->cam->plane_x * sc->cam->x;
	sc->ray->dir_y = sc->player->dir_y + sc->cam->plane_y * sc->cam->x;
	sc->map->map_x = (int)sc->player->pos_x;
	sc->map->map_y = (int)sc->player->pos_y;
	sc->ray->delta_dist_x = fabs(1 / sc->ray->dir_x);
	sc->ray->delta_dist_y = fabs(1 / sc->ray->dir_y);
	sc->ray->hit = 0;
}

void	init_texture(t_scene *sc, char *row, int i)
{
	static int	init_tex = 0;

	if (!init_tex)
	{
		init_tex = 1;
		sc->texture = (int **)malloc(sizeof(int *) * 8);
		if (!sc->texture)
			perror("Error in texture allocation\n");
		texture_cycle(sc);
	}
	read_texture_file_data(sc, row, i);
}
