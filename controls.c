#include "cub3d.h"


int	key_press(int keycode, void *param)
{
	t_scene *sc = (t_scene *)param;
	//printf("keycode = %d\n ", keycode); 
	if (keycode == 119)
		sc->player->posY -= 5;
	else if (keycode == 97) // A
		sc->player->posX -= 5;
	else if (keycode == 100) // S
		sc->player->posX += 5;
	else if (keycode == 115) // D
		sc->player->posY += 5;
	
	draw_map_2D(sc);
	draw_player(sc);

	return (0);
}
