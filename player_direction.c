/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:56:39 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:56:41 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_north(t_scene *sc)
{
	sc->player->dir_x = -1;
	sc->player->dir_y = 0;
	sc->cam->plane_x = 0;
	sc->cam->plane_y = 0.66f;
}

static void	set_player_south(t_scene *sc)
{
	sc->player->dir_x = 1;
	sc->player->dir_y = 0;
	sc->cam->plane_x = 0;
	sc->cam->plane_y = -0.66f;
}

static void	set_player_west(t_scene *sc)
{
	sc->player->dir_x = 0;
	sc->player->dir_y = -1;
	sc->cam->plane_x = -0.66f;
	sc->cam->plane_y = 0;
}

static void	set_player_east(t_scene *sc)
{
	sc->player->dir_x = 0;
	sc->player->dir_y = 1;
	sc->cam->plane_x = 0.66f;
	sc->cam->plane_y = 0;
}

void	put_player_on_map(t_scene *sc, char dir, int x, int y)
{
	if (dir == 'N')
		set_player_north(sc);
	else if (dir == 'S')
		set_player_south(sc);
	else if (dir == 'W')
		set_player_west(sc);
	else if (dir == 'E')
		set_player_east(sc);
	sc->player->pos_x = (double)x + 0.2f;
	sc->player->pos_y = (double)y + 0.2f;
}
