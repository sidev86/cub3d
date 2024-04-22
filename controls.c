#include "cub3d.h"

void	move_up(t_scene *sc)
{
	if (sc->map->room[(int)(sc->player->posX
				+ sc->player->dirX)][(int)(sc->player->posY)] == 0)
			sc->player->posX += sc->player->dirX;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			+ sc->player->dirY)] == 0)
		sc->player->posY += sc->player->dirY;
}

void	move_left(t_scene *sc)
{
	if (sc->map->room[(int)(sc->player->posX
				- sc->player->dirY)][(int)(sc->player->posY)] == 0)
			sc->player->posX -= sc->player->dirY;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			+ sc->player->dirX)] == 0)
		sc->player->posY += sc->player->dirX;
}

void	move_right(t_scene *sc)
{
	printf("posX = %d\n", (int)sc->player->posX);
	if (sc->map->room[(int)(sc->player->posX
			+ sc->player->dirY)][(int)(sc->player->posY)] == 0)
		sc->player->posX += sc->player->dirY;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			- sc->player->dirX)] == 0)
		sc->player->posY -= sc->player->dirX;
}

void	move_down(t_scene *sc)
{
	if (sc->map->room[(int)(sc->player->posX
				- sc->player->dirX)][(int)(sc->player->posY)] == 0)
			sc->player->posX -= sc->player->dirX;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			- sc->player->dirY)] == 0)
		sc->player->posY -= sc->player->dirY;
}


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
int	key_press(int keycode, void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	printf("keycode = %d\n ", keycode);
	if (keycode == 119) // W
		move_up(sc);
	else if (keycode == 97) // A
		move_left(sc);
	else if (keycode == 100) // D
		move_right(sc);
	else if (keycode == 115) // S
		move_down(sc); 
	else if (keycode == 65361) // left arrow
		rotate_left(sc);
	else if (keycode == 65363) // right arrow
		rotate_right(sc);
	else if (keycode == 65307)
		close_window(sc);
	// draw_map_2D(sc);
	// draw_player(sc);
	mlx_clear_window(sc->mlx, sc->win);
	scene_loop(sc);
	return (0);
}
