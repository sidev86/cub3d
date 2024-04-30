#include "cub3d.h"

static void	init_player(t_scene *sc)
{
	sc->player = malloc(sizeof(t_player));
	if (!sc->player)
		perror("Error in player allocation\n");
	sc->player->pos_x = 2.0f;
	sc->player->pos_y = 7.0f;
	sc->player->dir_x = -1;
	sc->player->dir_y = 0;
	sc->player->olddir_x = 0;
	sc->player->old_plane_x = 0;
	sc->player->move_speed = 0.05f;
	sc->player->rot_speed = 0.05f;
	sc->player->size = 10;
	sc->player->angle = (3 * PI) / 2;
	sc->player->delta_x = cos(sc->player->angle) * 5;
	sc->player->delta_y = sin(sc->player->angle) * 5;
}

static void	init_config_flags(t_scene *sc)
{
	int	i;

	sc->f = 0;
	sc->c = 0;
	sc->no = 0;
	sc->so = 0;
	sc->we = 0;
	sc->ea = 0;
	sc->text_init = 0;
	i = 0;
	while (i < 3)
	{
		sc->floor[i] = 0;
		sc->ceil[i] = 0;
		i++;
	}
}

static void	read_data_before_map(t_scene *sc, char *path, int *fd)
{
	char	*row;
	int		lines;

	lines = 0;
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		free_invalid_map(sc, 'f');
	check_file_extension(sc, path);
	while (*fd != -1)
	{
		row = get_next_line(*fd);
		skip_empty_lines(&row, fd);
		if (!row)
			free_empty_file(sc);
		read_config_lines(sc, &row, &lines);
		free(row);
		if (lines == 6)
			break ;
	}
}

static void	init_map(t_scene *sc, int *fd)
{
	char	*row;
	int		i;

	sc->map = malloc(sizeof(t_map));
	sc->map->rows = 0;
	sc->map->cols = 0;
	sc->map->map_present = 0;
	read_map_for_init(sc, &row, fd);
	sc->map->room = (char **)malloc(sizeof(char *) * sc->map->rows);
	i = 0;
	while (i < sc->map->rows)
	{
		sc->map->room[i] = (char *)malloc(sizeof(char) * sc->map->cols);
		i++;
	}
	sc->map->map_x = sc->map->rows;
	sc->map->map_y = sc->map->cols;
	sc->map->map_size = sc->map->cols * sc->map->rows;
	close(*fd);
}

void	init_scene(t_scene *sc, char *path)
{
	int	fd;

	sc->color = 0xFFFF00;
	sc->re_buf = 0;
	init_config_flags(sc);
	init_player(sc);
	read_data_before_map(sc, path, &fd);
	init_map(sc, &fd);
	clear_buffer(sc);
	sc->cam = malloc(sizeof(t_camera));
	sc->cam->plane_x = 0;
	sc->cam->plane_y = 0.66f;
	sc->cam->x = 0;
	sc->ray = malloc(sizeof(t_ray));
}
