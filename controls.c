/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:53:39 by sibrahim          #+#    #+#             */
/*   Updated: 2024/05/04 11:53:46 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	if (keycode == 119)
		move_up(sc);
	else if (keycode == 97)
		move_left(sc);
	else if (keycode == 100)
		move_right(sc);
	else if (keycode == 115)
		move_down(sc);
	else if (keycode == 65361)
		rotate_left(sc);
	else if (keycode == 65363)
		rotate_right(sc);
	else if (keycode == 65307)
		close_window(sc);
	mlx_clear_window(sc->mlx, sc->win);
	scene_loop(sc);
	return (0);
}
