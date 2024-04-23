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
	{
		printf("Error! Double key rows(floor/ceiling)\n");
		free_doublerow_ceilfloor(sc, row);
		exit(0);
	}
}

void	set_initial_ray_data(t_scene *sc, int x)
{
	sc->cam->x = 2 * x / (double)W_WIDTH - 1;
	sc->ray->dirX = sc->player->dirX + sc->cam->planeX * sc->cam->x;
	sc->ray->dirY = sc->player->dirY + sc->cam->planeY * sc->cam->x;
	sc->map->mapX = (int)sc->player->posX;
	sc->map->mapY = (int)sc->player->posY;
	sc->ray->deltaDistX = fabs(1 / sc->ray->dirX);
	sc->ray->deltaDistY = fabs(1 / sc->ray->dirY);
	sc->ray->hit = 0; 
}

void	init_texture(t_scene *sc,char *row, int i)
{
	static int init_tex = 0;
	
	if (!init_tex)
	{
		init_tex = 1; 
		sc->texture = (int **)malloc(sizeof(int *) * 8);
		if (!sc->texture)
			printf("Error in texture allocation\n");
		texture_cycle(sc);
	}
	read_texture_file_data(sc, row, i);
	//load_texture(sc);
}
