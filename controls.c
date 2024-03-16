#include "cub3d.h"


int	key_press(int keycode, void *param)
{
	t_scene *sc = (t_scene *)param;
	printf("keycode = %d\n ", keycode); 
	if (keycode == 119) // W
	{
		sc->player->posX += sc->player->deltaX;
		sc->player->posY += sc->player->deltaY;
	}
	else if (keycode == 97) // A
	{
		//sc->player->posX -= 5;
		sc->player->angle-=0.1f;
		if (sc->player->angle < 0)
			sc->player->angle += 2 * PI;
		sc->player->deltaX = cos(sc->player->angle) * 5;
		sc->player->deltaY = sin(sc->player->angle) * 5;
	}
	else if (keycode == 100) // D
	{
		//sc->player->posX += 5;
		sc->player->angle+=0.1f;
		if (sc->player->angle > 2 * PI)
			sc->player->angle -= 2 * PI;
		sc->player->deltaX = cos(sc->player->angle) * 5;
		sc->player->deltaY = sin(sc->player->angle) * 5;
	}
	else if (keycode == 115) // S
	{
		sc->player->posX -= sc->player->deltaX;
		sc->player->posY -= sc->player->deltaY;
		
	}
	
	draw_map_2D(sc);
	draw_player(sc);

	return (0);
}
