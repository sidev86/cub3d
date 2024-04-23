#include "cub3d.h"

int	key_press(int keycode, void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	printf("keycode = %d\n ", keycode);
	if (keycode == 119) // W
		move_up(sc);
	else if (keycode == 97) // A
		move_left(sc);
	else if (keycode == 100) // D
		move_right(sc);
	else if (keycode == 115) // S
		move_down(sc); 
	else if (keycode == 65361) // left arrow
		rotate_left(sc);
	else if (keycode == 65363) // right arrow
		rotate_right(sc);
	else if (keycode == 65307)
		close_window(sc);
	// draw_map_2D(sc);
	// draw_player(sc);
	mlx_clear_window(sc->mlx, sc->win);
	scene_loop(sc);
	return (0);
}
