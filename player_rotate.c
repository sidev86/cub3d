#include "cub3d.h"

void	rotate_left(t_scene *sc)
{
	double r;
	
	r = sc->player->rotSpeed;
	sc->player->oldDirX = sc->player->dirX;
	sc->player->dirX = sc->player->dirX * cos(r) - sc->player->dirY
		* sin(r);
	sc->player->dirY = sc->player->oldDirX * sin(r) + sc->player->dirY * cos(r);
	sc->player->oldPlaneX = sc->cam->planeX;
	sc->cam->planeX = sc->cam->planeX * cos(r) - sc->cam->planeY
		* sin(r);
	sc->cam->planeY = sc->player->oldPlaneX * sin(r) + sc->cam->planeY * cos(r);
}

void	rotate_right(t_scene *sc)
{
	double r;
	
	r = sc->player->rotSpeed;
	sc->player->oldDirX = sc->player->dirX;
	sc->player->dirX = sc->player->dirX * cos(-r) - sc->player->dirY
		* sin(-r);
	sc->player->dirY = sc->player->oldDirX * sin(-r) + sc->player->dirY * cos(-r);
	sc->player->oldPlaneX = sc->cam->planeX;
	sc->cam->planeX = sc->cam->planeX * cos(-r) - sc->cam->planeY
		* sin(-r);
	sc->cam->planeY = sc->player->oldPlaneX * sin(-r) + sc->cam->planeY * cos(-r);
}
