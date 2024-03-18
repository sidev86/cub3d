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

static float dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}


void	draw_rays_3D(t_scene *sc)
{
	float aTan;
	float nTan;
	int p1[2];
	int p2[2];
	
	sc->ray->angle = sc->player->angle;
	//p1[0] = sc->player->posX;
	//p1[1] = sc->player->posY;
	//p2[0] = p1[0] + sc->player->deltaX * 5;
	//p2[1] = p1[1] + sc->player->deltaY * 5;
	for (int r = 0; r < 1; r++)
	{
		
		//Check wall horizontal lines
		sc->ray->dof = 0;
		sc->ray->disH = 1000000;
		sc->ray->hx = sc->player->posX;
		sc->ray->hy = sc->player->posY;
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
			if (sc->ray->mp < sc->map->mapX * sc->map->mapY && sc->ray->mp > 0 && sc->map->values[sc->ray->mp] == 1)
			{
				sc->ray->hx = sc->ray->rx;
				sc->ray->hy = sc->ray->ry;
				sc->ray->disH = dist(sc->player->posX, sc->player->posY, sc->ray->hx, sc->ray->hy);
				sc->ray->dof = 8;
			}
			else
			{
				sc->ray->rx += sc->ray->xo;
				sc->ray->ry += sc->ray->yo;
				sc->ray->dof += 1;
			}
		}
		
		
		//Check wall vertical lines
		sc->ray->dof = 0;
		sc->ray->disV = 1000000;
		sc->ray->vx = sc->player->posX;
		sc->ray->vy = sc->player->posY;
		nTan = -tan(sc->ray->angle);
		if (sc->ray->angle > PI / 2 && sc->ray->angle < 3 * PI / 2)
		{
			sc->ray->rx = (((int)sc->player->posX >> 6) << 6) -0.0001; 
			sc->ray->ry = (sc->player->posX - sc->ray->rx) * nTan + sc->player->posY;
			sc->ray->xo = -64;
			sc->ray->yo = -(sc->ray->xo) * nTan;
		}	
		if (sc->ray->angle < PI / 2 || sc->ray->angle > 3 * PI / 2)
		{
			sc->ray->rx = (((int)sc->player->posX >> 6) << 6) + 64; 
			sc->ray->ry = (sc->player->posX - sc->ray->rx) * nTan + sc->player->posY;
			sc->ray->xo = 64;
			sc->ray->yo = -(sc->ray->xo) * nTan;
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
			if (sc->ray->mp < sc->map->mapX * sc->map->mapY && sc->ray->mp > 0 && sc->map->values[sc->ray->mp] == 1)
			{
				sc->ray->vx = sc->ray->rx;
				sc->ray->vy = sc->ray->ry;
				sc->ray->disV = dist(sc->player->posX, sc->player->posY, sc->ray->vx, sc->ray->vy);
				sc->ray->dof = 8;
			}
			else
			{
				sc->ray->rx += sc->ray->xo;
				sc->ray->ry += sc->ray->yo;
				sc->ray->dof += 1;
			}
		}
		
		if (sc->ray->disV < sc->ray->disH)
		{
			sc->ray->rx = sc->ray->vx; 
			sc->ray->ry = sc->ray->vy;
		}
		if (sc->ray->disH < sc->ray->disV)
		{
			sc->ray->rx = sc->ray->hx; 
			sc->ray->ry = sc->ray->hy;
		}
		
		p1[0] = (int)sc->player->posX;
		p1[1] = (int)sc->player->posY;
		p2[0] = (int)sc->ray->rx;
		p2[1] = (int)sc->ray->ry;
		
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
