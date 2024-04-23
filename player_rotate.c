#include "cub3d.h"

void	rotate_left(t_scene *sc)
{
	sc->player->oldDirX = sc->player->dirX;
	sc->player->dirX = sc->player->dirX * cos(0.1f) - sc->player->dirY
		* sin(0.1f);
	sc->player->dirY = sc->player->oldDirX * sin(0.1f) + sc->player->dirY * cos(0.1f);
	sc->player->oldPlaneX = sc->cam->planeX;
	sc->cam->planeX = sc->cam->planeX * cos(0.1f) - sc->cam->planeY
		* sin(0.1f);
	sc->cam->planeY = sc->player->oldPlaneX * sin(0.1f) + sc->cam->planeY * cos(0.1f);
}

void	rotate_right(t_scene *sc)
{
	sc->player->oldDirX = sc->player->dirX;
	sc->player->dirX = sc->player->dirX * cos(-0.1f) - sc->player->dirY
		* sin(-0.1f);
	sc->player->dirY = sc->player->oldDirX * sin(-0.1f) + sc->player->dirY * cos(-0.1f);
	sc->player->oldPlaneX = sc->cam->planeX;
	sc->cam->planeX = sc->cam->planeX * cos(-0.1f) - sc->cam->planeY
		* sin(-0.1f);
	sc->cam->planeY = sc->player->oldPlaneX * sin(-0.1f) + sc->cam->planeY * cos(-0.1f);
}
