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
		put_pixel(sc, cur[0], cur[1], sc->color);
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
