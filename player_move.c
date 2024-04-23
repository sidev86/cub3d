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
