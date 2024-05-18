/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:56:54 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:56:56 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_scene *sc)
{
	double	r;

	r = sc->player->rot_speed;
	sc->player->olddir_x = sc->player->dir_x;
	sc->player->dir_x = sc->player->dir_x * cos(r) - sc->player->dir_y * sin(r);
	sc->player->dir_y = sc->player->olddir_x * sin(r) + sc->player->dir_y
		* cos(r);
	sc->player->old_plane_x = sc->cam->plane_x;
	sc->cam->plane_x = sc->cam->plane_x * cos(r) - sc->cam->plane_y * sin(r);
	sc->cam->plane_y = sc->player->old_plane_x * sin(r) + sc->cam->plane_y
		* cos(r);
}

void	rotate_right(t_scene *sc)
{
	double	r;

	r = sc->player->rot_speed;
	sc->player->olddir_x = sc->player->dir_x;
	sc->player->dir_x = sc->player->dir_x * cos(-r) - sc->player->dir_y
		* sin(-r);
	sc->player->dir_y = sc->player->olddir_x * sin(-r) + sc->player->dir_y
		* cos(-r);
	sc->player->old_plane_x = sc->cam->plane_x;
	sc->cam->plane_x = sc->cam->plane_x * cos(-r) - sc->cam->plane_y * sin(-r);
	sc->cam->plane_y = sc->player->old_plane_x * sin(-r) + sc->cam->plane_y
		* cos(-r);
}
