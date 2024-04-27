#include "cub3d.h"

void	init_player(t_scene *sc)
{
	sc->player = malloc(sizeof(t_player));
	if (!sc->player)
		printf("Error in player allocation\n");
	sc->player->posX = 2.0f;
	sc->player->posY = 7.0f;
	sc->player->dirX = -1;
	sc->player->dirY = 0;
	sc->player->oldDirX = 0;
	sc->player->oldPlaneX = 0;
	sc->player->moveSpeed = 0.05f;
	sc->player->rotSpeed = 0.05f;
	sc->player->size = 10;
	sc->player->angle = (3 * PI) / 2;
	sc->player->deltaX = cos(sc->player->angle) * 5;
	sc->player->deltaY = sin(sc->player->angle) * 5;
}

void	init_config_flags(t_scene *sc)
{
	sc->f = 0;
	sc->c = 0;
	sc->no = 0;
	sc->so = 0;
	sc->we = 0;
	sc->ea = 0;
	sc->text_init = 0;
	int i = 0;
	while (i < 3)
	{
		sc->floor[i] = 0;
		sc->ceil[i] = 0;
		i++;
	}
}

void 	read_data_before_map(t_scene *sc, char *path, int *fd)
{
	char *row;
	int lines = 0;
	
	//i = 0;
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		printf("Error while opening file\n");
	check_file_extension(sc, path);
	while (*fd != -1)
	{
		//i = 0;
		row = get_next_line(*fd);
		skip_empty_lines(&row, fd);
		if (!row)
			free_empty_file(sc);
		read_config_lines(sc, &row, &lines);
		free(row);
		if (lines == 6)
			break;	
	}	
}

void	init_map(t_scene *sc, int *fd)
{
	
	char *row;
	int i;
	
	//row = NULL;
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
	//printf("map rows = %d\n", rows);
	sc->map->mapX = sc->map->rows;
	//sc->rows = sc->map->rows;
	sc->map->mapY = sc->map->cols;
	sc->map->mapSize = sc->map->cols * sc->map->rows;
	close(*fd);
}

void	init_scene(t_scene *sc, char *path)
{
	int fd;
	sc->color = 0xFFFF00;
	sc->re_buf = 0;
	init_config_flags(sc);
	init_player(sc);
	read_data_before_map(sc, path, &fd);
	init_map(sc, &fd);
	clear_buffer(sc);
	
	//init cam
	sc->cam = malloc(sizeof(t_camera));
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;
	sc->cam->x = 0;

	sc->ray = malloc(sizeof(t_ray));
}


