#include "cub3d.h"

void	set_ray_steps(t_scene *sc)
{
	if (sc->ray->dirX < 0)
	{
    		sc->ray->stepX = -1;
    		sc->ray->sideDistX = (sc->player->posX - sc->map->mapX) * sc->ray->deltaDistX;
	}
	else
	{
    		sc->ray->stepX = 1;
    		sc->ray->sideDistX = (sc->map->mapX + 1.0f - sc->player->posX) * sc->ray->deltaDistX;
	}
	if (sc->ray->dirY < 0)
	{
	    sc->ray->stepY = -1;
	    sc->ray->sideDistY = (sc->player->posY - sc->map->mapY) * sc->ray->deltaDistY;
	}
	else
	{
   		sc->ray->stepY = 1;
    		sc->ray->sideDistY = (sc->map->mapY + 1.0 - sc->player->posY) * sc->ray->deltaDistY;
	}
}


void	check_shortest_hit(t_scene *sc)
{
	while (!sc->ray->hit)
	{
		if (sc->ray->sideDistX < sc->ray->sideDistY)
		{
			sc->ray->sideDistX += sc->ray->deltaDistX;
			sc->map->mapX += sc->ray->stepX;
			sc->ray->side = 0; // L'intersezione è orizzontale
		}
	    	else
	    	{
			sc->ray->sideDistY += sc->ray->deltaDistY;
			sc->map->mapY += sc->ray->stepY;
			sc->ray->side = 1; // L'intersezione è verticale
	    	}
    		if (sc->map->room[sc->map->mapX][sc->map->mapY] > 0)
		sc->ray->hit = 1;
	}
}

void	calculate_for_draw(t_scene *sc)
{
	if (sc->ray->side == 0)
    		sc->ray->perpWallDist = (sc->map->mapX - sc->player->posX + (1 - sc->ray->stepX) / 2) / sc->ray->dirX;
	else
    		sc->ray->perpWallDist = (sc->map->mapY - sc->player->posY + (1 - sc->ray->stepY) / 2) / sc->ray->dirY;

	sc->ray->lineHeight = (int)(W_HEIGHT / sc->ray->perpWallDist);
	sc->ray->drawStart = -sc->ray->lineHeight / 2 + W_HEIGHT / 2;
	if (sc->ray->drawStart < 0)
    		sc->ray->drawStart = 0;
	sc->ray->drawEnd = sc->ray->lineHeight / 2 + W_HEIGHT / 2;
	if (sc->ray->drawEnd >= W_HEIGHT)
    		sc->ray->drawEnd = W_HEIGHT - 1;
	if (sc->ray->side == 0)
		sc->wallX = sc->player->posY + sc->ray->perpWallDist * sc->ray->dirY;
	else
		sc->wallX = sc->player->posX + sc->ray->perpWallDist * sc->ray->dirX;
	sc->wallX -= floor(sc->wallX);
	sc->texX = (int)(sc->wallX * (double)T_WIDTH);
	if (sc->ray->side == 0 && sc->ray->dirX > 0)
		sc->texX = T_WIDTH - sc->texX - 1;
	if (sc->ray->side == 1 && sc->ray->dirY < 0)
		sc->texX = T_WIDTH - sc->texX - 1;
	sc->step = 1.0 * T_HEIGHT / sc->ray->lineHeight;
	sc->texPos = (sc->ray->drawStart - W_HEIGHT / 2 + sc->ray->lineHeight / 2) * sc->step;
}

void	texture_to_draw(t_scene *sc, int x)
{
	for (int y = sc->ray->drawStart; y < sc->ray->drawEnd; y++)
	{
		sc->texY = (int)sc->texPos & (T_HEIGHT - 1);
		sc->texPos += sc->step;
		if (sc->ray->side == 0 && sc->map->mapX >= sc->player->posX)
			sc->color = sc->texture[0][T_HEIGHT * sc->texY + sc->texX];
		else if (sc->ray->side == 0 && sc->map->mapX < sc->player->posX)
			sc->color = sc->texture[1][T_HEIGHT * sc->texY + sc->texX];
		else if (sc->ray->side == 1 && sc->map->mapY >= sc->player->posY)
			sc->color = sc->texture[2][T_HEIGHT * sc->texY + sc->texX];
		else if (sc->ray->side == 1 && sc->map->mapY < sc->player->posY)
			sc->color = sc->texture[3][T_HEIGHT * sc->texY + sc->texX];
		if (sc->ray->side == 1)
			sc->color = (sc->color >> 1) & 8355711;
		sc->buff[y][x] = sc->color;
		sc->re_buf = 1;
	}
}

void	calculate_rays(t_scene *sc)
{
	int x;

	x = 0;
	if (sc->re_buf == 1)
		clear_buffer(sc);
	draw_floor_ceiling(sc);
	while (x < W_WIDTH)
	{
		set_initial_ray_data(sc, x);
		set_ray_steps(sc);
		check_shortest_hit(sc);
		calculate_for_draw(sc);
		texture_to_draw(sc, x);
		x++;
	}

}


