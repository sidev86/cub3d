/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:56:46 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:56:47 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_scene *sc)
{
	double	m;

	m = sc->player->move_speed;
	if (sc->map->room[(int)(sc->player->pos_x + sc->player->dir_x * m
			* 2)][(int)(sc->player->pos_y)] == '0')
		sc->player->pos_x += sc->player->dir_x * m;
	if (sc->map->room[(int)(sc->player->pos_x)][(int)(sc->player->pos_y
			+ sc->player->dir_y * m * 2)] == '0')
		sc->player->pos_y += sc->player->dir_y * m;
}

void	move_left(t_scene *sc)
{
	double	m;

	m = sc->player->move_speed;
	if (sc->map->room[(int)(sc->player->pos_x - sc->player->dir_y * m
			* 2)][(int)(sc->player->pos_y)] == '0')
		sc->player->pos_x -= sc->player->dir_y * m;
	if (sc->map->room[(int)(sc->player->pos_x)][(int)(sc->player->pos_y
			+ sc->player->dir_x * m * 2)] == '0')
		sc->player->pos_y += sc->player->dir_x * m;
}

void	move_right(t_scene *sc)
{
	double	m;

	m = sc->player->move_speed;
	if (sc->map->room[(int)(sc->player->pos_x + sc->player->dir_y * m
			* 2)][(int)(sc->player->pos_y)] == '0')
		sc->player->pos_x += sc->player->dir_y * m;
	if (sc->map->room[(int)(sc->player->pos_x)][(int)(sc->player->pos_y
			- sc->player->dir_x * m * 2)] == '0')
		sc->player->pos_y -= sc->player->dir_x * m;
}

void	move_down(t_scene *sc)
{
	double	m;

	m = sc->player->move_speed;
	if (sc->map->room[(int)(sc->player->pos_x - sc->player->dir_x * m
			* 2)][(int)(sc->player->pos_y)] == '0')
		sc->player->pos_x -= sc->player->dir_x * m;
	if (sc->map->room[(int)(sc->player->pos_x)][(int)(sc->player->pos_y
			- sc->player->dir_y * m * 2)] == '0')
		sc->player->pos_y -= sc->player->dir_y * m;
}
