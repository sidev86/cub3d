#include "cub3d.h"

static int	*calculate_sign(int p1x, int p1y, int p2x, int p2y)
{
	int	*sign;
	
	sign = malloc(sizeof(int) * 2);
	if (p1x < p2x)
		sign[0] = 1;
	else
		sign[0] = -1;
	if (p1y < p2y)
		sign[1] = 1;
	else
		sign[1] = -1;
	return (sign);
}

static int	*absolute_delta(int p1x, int p1y, int p2x, int p2y)
{
	int	*delta;

	delta = malloc(sizeof(int) * 2);
	delta[0] = abs(p2x - p1x);
	delta[1] = abs(p2y - p1y);
	return (delta);
}

void	draw_rays_3D(t_scene *sc)
{
	float aTan;
	int p1[2];
	int p2[2];
	
	sc->ray->angle = sc->player->angle;
	p1[0] = sc->player->posX;
	p1[1] = sc->player->posY;
	p2[0] = p1[0] + sc->player->deltaX * 5;
	p2[1] = p1[1] + sc->player->deltaY * 5;
	for (int r = 0; r < 1; r++)
	{
		sc->ray->dof = 0;
		aTan = -1/(tan(sc->ray->angle));
		if (sc->ray->angle > PI)
		{
			sc->ray->ry = (((int)sc->player->posY >> 6) << 6) -0.0001; 
			sc->ray->rx = (sc->player->posY - sc->ray->ry) * aTan + sc->player->posX;
			sc->ray->yo = -64;
			sc->ray->xo = -(sc->ray->yo) * aTan;
		}	
		if (sc->ray->angle < PI)
		{
			sc->ray->ry = (((int)sc->player->posY >> 6) << 6) + 64; 
			sc->ray->rx = (sc->player->posY - sc->ray->ry) * aTan + sc->player->posX;
			sc->ray->yo = 64;
			sc->ray->xo = -(sc->ray->yo) * aTan;
		}	
		if (sc->ray->angle == 0 || sc->ray->angle == PI)
		{
			sc->ray->rx = sc->player->posX;
			sc->ray->ry = sc->player->posY;
			sc->ray->dof = 8;
		}
		while (sc->ray->dof < 8)
		{
			sc->ray->mx = (int)(sc->ray->rx) >> 6;
			sc->ray->my = (int)(sc->ray->ry) >> 6;
			sc->ray->mp = (sc->ray->my * sc->map->mapX) + sc->ray->mx;
			if (sc->ray->mp < sc->map->mapX * sc->map->mapY && sc->map->values[sc->ray->mp] == 1)
				sc->ray->dof = 8;
			else
			{
				sc->ray->rx += sc->ray->xo;
				sc->ray->ry += sc->ray->yo;
				sc->ray->dof += 1;
			}
		}
		p1[0] = sc->player->posX;
		p1[1] = sc->player->posY;
		p2[0] = sc->ray->rx;
		p2[1] = sc->ray->ry;
		draw_line(sc, p1, p2);
	}


}

void	draw_line(t_scene *sc, int *p1, int *p2)
{
	int *delta;
	int *sign;
	int cur[2];
	int		e1;
	int		e2;

	delta = absolute_delta(p1[0], p1[1], p2[0], p2[1]);
	sign = calculate_sign(p1[0], p1[1], p2[0], p2[1]);
	e1 = delta[0] - delta[1];
	cur[0] = p1[0];
	cur[1] = p1[1]; 
	while (cur[0] != p2[0] || cur[1] != p2[1])
	{
		put_pixel(sc, cur[0], cur[1], 0x00FF00);
		e2 = e1 * 2;
		if (e2 > -delta[1])
		{
			e1 -= delta[1];
			cur[0] += sign[0];
		}
		if (e2 < delta[0])
		{
			e1 += delta[0];
			cur[1] += sign[1];
		}
	}
}
