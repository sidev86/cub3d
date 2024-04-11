#include "cub3d.h"


int	key_press(int keycode, void *param)
{
	t_scene *sc = (t_scene *)param;
	printf("keycode = %d\n ", keycode); 
	//printf("player posX = %f\n", sc->player->posX);
	//printf("player posY = %f\n", sc->player->posY);
	if (keycode == 119) // W
	{
		if(sc->map->room[(int)(sc->player->posX + sc->player->dirX)][(int)(sc->player->posY)] == 0) 
			sc->player->posX += sc->player->dirX;
      		if(sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY + sc->player->dirY)] == 0) 
			sc->player->posY += sc->player->dirY;
	}
	else if (keycode == 97) // A
	{
		if(sc->map->room[(int)(sc->player->posX - sc->player->dirY)][(int)(sc->player->posY)] == 0) 
			sc->player->posX -= sc->player->dirY;
      		if(sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY + sc->player->dirX)] == 0) 
			sc->player->posY += sc->player->dirX;
	}
	else if (keycode == 100) // D
	{
		printf("posX = %d\n", (int)sc->player->posX);
		if(sc->map->room[(int)(sc->player->posX + sc->player->dirY)][(int)(sc->player->posY)] == 0) 
			sc->player->posX += sc->player->dirY;
		if(sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY - sc->player->dirX)] == 0) 
			sc->player->posY -= sc->player->dirX;
	}
	
	else if (keycode == 115) // S
	{
		if(sc->map->room[(int)(sc->player->posX - sc->player->dirX)][(int)(sc->player->posY)] == 0) 
			sc->player->posX -= sc->player->dirX;
      		if(sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY - sc->player->dirY)] == 0) 
			sc->player->posY -= sc->player->dirY;
		
	}
	else if (keycode == 65361) // left arrow
	{
		double oldDirX = sc->player->dirX;
		sc->player->dirX = sc->player->dirX * cos(0.1f) - sc->player->dirY * sin(0.1f);
		sc->player->dirY = oldDirX * sin(0.1f) + sc->player->dirY * cos(0.1f);
		double oldPlaneX = sc->cam->planeX;
		sc->cam->planeX = sc->cam->planeX * cos(0.1f) - sc->cam->planeY * sin(0.1f);
		sc->cam->planeY = oldPlaneX * sin(0.1f) + sc->cam->planeY * cos(0.1f);
	}
	else if (keycode == 65363) // right arrow
	{
		double oldDirX = sc->player->dirX;
		sc->player->dirX = sc->player->dirX * cos(-0.1f) - sc->player->dirY * sin(-0.1f);
		sc->player->dirY = oldDirX * sin(-0.1f) + sc->player->dirY * cos(-0.1f);
		double oldPlaneX = sc->cam->planeX;
		sc->cam->planeX = sc->cam->planeX * cos(-0.1f) - sc->cam->planeY * sin(-0.1f);
		sc->cam->planeY = oldPlaneX * sin(-0.1f) + sc->cam->planeY * cos(-0.1f);
	}
	else if (keycode == 65307)
		close_window(sc);
	
	//draw_map_2D(sc);
	//draw_player(sc);
	mlx_clear_window(sc->mlx, sc->win);
	scene_loop(sc);
	return (0);
}
