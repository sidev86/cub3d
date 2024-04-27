#include "cub3d.h"

void	move_up(t_scene *sc)
{
	double m;
	m = sc->player->moveSpeed;
	
	if (sc->map->room[(int)(sc->player->posX
				+ sc->player->dirX * m * 2)][(int)(sc->player->posY)] == '0')
			sc->player->posX += sc->player->dirX * m;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			+ sc->player->dirY * m * 2)] == '0')
		sc->player->posY += sc->player->dirY * m;
}

void	move_left(t_scene *sc)
{
	double m;
	
	m = sc->player->moveSpeed;
	if (sc->map->room[(int)(sc->player->posX
				- sc->player->dirY * m * 2)][(int)(sc->player->posY)] == '0')
			sc->player->posX -= sc->player->dirY * m;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			+ sc->player->dirX * m * 2)] == '0')
		sc->player->posY += sc->player->dirX * m;
}

void	move_right(t_scene *sc)
{
	double m;
	
	m = sc->player->moveSpeed;
	if (sc->map->room[(int)(sc->player->posX
			+ sc->player->dirY * m * 2)][(int)(sc->player->posY)] == '0')
		sc->player->posX += sc->player->dirY * m;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			- sc->player->dirX * m * 2)] == '0')
		sc->player->posY -= sc->player->dirX * m;
}

void	move_down(t_scene *sc)
{
	double m;
	
	m = sc->player->moveSpeed;
	if (sc->map->room[(int)(sc->player->posX
				- sc->player->dirX * m * 2)][(int)(sc->player->posY)] == '0')
			sc->player->posX -= sc->player->dirX * m;
	if (sc->map->room[(int)(sc->player->posX)][(int)(sc->player->posY
			- sc->player->dirY * m * 2)] == '0')
		sc->player->posY -= sc->player->dirY * m;
}
