#include "cub3d.h"

static void	set_player_north(t_scene *sc)
{
	sc->player->dirX = -1;
	sc->player->dirY = 0;
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;
}

static void	set_player_south(t_scene *sc)
{
	sc->player->dirX = 1;
	sc->player->dirY = 0;
	sc->cam->planeX = 0;
	sc->cam->planeY = -0.66f;
}

static void	set_player_west(t_scene *sc)
{
	sc->player->dirX = 0;
	sc->player->dirY = -1;
	sc->cam->planeX = -0.66f;
	sc->cam->planeY = 0;
}

static void	set_player_east(t_scene *sc)
{
	sc->player->dirX = 0;
	sc->player->dirY = 1;
	sc->cam->planeX = 0.66f;
	sc->cam->planeY = 0;
}

void put_player_on_map(t_scene *sc, char dir, int x, int y)
{
	if (dir == 'N')
		set_player_north(sc);
	else if (dir == 'S')
		set_player_south(sc);
	else if (dir == 'W')
		set_player_west(sc);
	else if (dir == 'E')
		set_player_east(sc);
	sc->player->posX = (double)x + 0.2f;
	sc->player->posY = (double)y + 0.2f;
}
