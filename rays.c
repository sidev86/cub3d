#include "cub3d.h"

void	set_ray_steps(t_scene *sc)
{
	if (sc->ray->dir_x < 0)
	{
		sc->ray->step_x = -1;
		sc->ray->side_dist_x = (sc->player->pos_x - sc->map->map_x)
			* sc->ray->delta_dist_x;
	}
	else
	{
		sc->ray->step_x = 1;
		sc->ray->side_dist_x = (sc->map->map_x + 1.0f - sc->player->pos_x)
			* sc->ray->delta_dist_x;
	}
	if (sc->ray->dir_y < 0)
	{
		sc->ray->step_y = -1;
		sc->ray->side_dist_y = (sc->player->pos_y - sc->map->map_y)
			* sc->ray->delta_dist_y;
	}
	else
	{
		sc->ray->step_y = 1;
		sc->ray->side_dist_y = (sc->map->map_y + 1.0 - sc->player->pos_y)
			* sc->ray->delta_dist_y;
	}
}

void	check_shortest_hit(t_scene *sc)
{
	while (!sc->ray->hit)
	{
		if (sc->ray->side_dist_x < sc->ray->side_dist_y)
		{
			sc->ray->side_dist_x += sc->ray->delta_dist_x;
			sc->map->map_x += sc->ray->step_x;
			sc->ray->side = 0;
		}
		else
		{
			sc->ray->side_dist_y += sc->ray->delta_dist_y;
			sc->map->map_y += sc->ray->step_y;
			sc->ray->side = 1;
		}
		if (sc->map->room[sc->map->map_x][sc->map->map_y] == '1')
			sc->ray->hit = 1;
	}
}

void	calculate_for_draw(t_scene *sc)
{
	if (sc->ray->side == 0)
		sc->ray->perp_wall_dist = (sc->map->map_x - sc->player->pos_x + (1
					- sc->ray->step_x) / 2) / sc->ray->dir_x;
	else
		sc->ray->perp_wall_dist = (sc->map->map_y - sc->player->pos_y + (1
					- sc->ray->step_y) / 2) / sc->ray->dir_y;
	sc->ray->line_height = (int)(W_HEIGHT / sc->ray->perp_wall_dist);
	sc->ray->draw_start = -sc->ray->line_height / 2 + W_HEIGHT / 2;
	if (sc->ray->draw_start < 0)
		sc->ray->draw_start = 0;
	sc->ray->draw_end = sc->ray->line_height / 2 + W_HEIGHT / 2;
	if (sc->ray->draw_end >= W_HEIGHT)
		sc->ray->draw_end = W_HEIGHT - 1;
	if (sc->ray->side == 0)
		sc->wall_x = sc->player->pos_y + sc->ray->perp_wall_dist
			* sc->ray->dir_y;
	else
		sc->wall_x = sc->player->pos_x + sc->ray->perp_wall_dist
			* sc->ray->dir_x;
	sc->wall_x -= floor(sc->wall_x);
	sc->tex_x = (int)(sc->wall_x * (double)T_WIDTH);
	if (sc->ray->side == 0 && sc->ray->dir_x > 0)
		sc->tex_x = T_WIDTH - sc->tex_x - 1;
	if (sc->ray->side == 1 && sc->ray->dir_y < 0)
		sc->tex_x = T_WIDTH - sc->tex_x - 1;
	sc->step = 1.0 * T_HEIGHT / sc->ray->line_height;
	sc->tex_pos = (sc->ray->draw_start - W_HEIGHT / 2 + sc->ray->line_height
			/ 2) * sc->step;
}

void	texture_to_draw(t_scene *sc, int x)
{
	int		y;

	y = sc->ray->draw_start;
	while (y < sc->ray->draw_end)
	{
		sc->tex_y = (int)sc->tex_pos & (T_HEIGHT - 1);
		sc->tex_pos += sc->step;
		if (sc->ray->side == 0 && sc->map->map_x >= sc->player->pos_x)
			sc->color = sc->texture[0][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 0 && sc->map->map_x < sc->player->pos_x)
			sc->color = sc->texture[1][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 1 && sc->map->map_y >= sc->player->pos_y)
			sc->color = sc->texture[2][T_HEIGHT * sc->tex_y + sc->tex_x];
		else if (sc->ray->side == 1 && sc->map->map_y < sc->player->pos_y)
			sc->color = sc->texture[3][T_HEIGHT * sc->tex_y + sc->tex_x];
		if (sc->ray->side == 1)
			sc->color = (sc->color >> 1) & 8355711;
		sc->buff[y][x] = sc->color;
		sc->re_buf = 1;
		y++;
	}
}

void	calculate_rays(t_scene *sc)
{
	int	x;

	x = 0;
	if (sc->re_buf == 1)
		clear_buffer(sc);
	draw_floor_ceiling(sc);
	while (x < W_WIDTH)
	{
		set_initial_ray_data(sc, x);
		set_ray_steps(sc);
		check_shortest_hit(sc);
		calculate_for_draw(sc);
		texture_to_draw(sc, x);
		x++;
	}
}
