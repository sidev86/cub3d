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
	sc->player->size = 10;
	sc->player->angle = (3 * PI) / 2;
	sc->player->deltaX = cos(sc->player->angle) * 5;
	sc->player->deltaY = sin(sc->player->angle) * 5;
}

void	init_texture(t_scene *sc,char *row, int i)
{
	static int init_tex = 0;
	
	if (!init_tex)
	{
		init_tex = 1; 
		sc->texture = (int **)malloc(sizeof(int *) * 8);
		if (!sc->texture)
			printf("Error in texture allocation\n");
		texture_cycle(sc);
	}
	read_texture_file_data(sc, row, i);
	//load_texture(sc);
}

void	read_map_for_init(t_scene *sc, char **row, int *fd)
{
	while (*fd != -1)
	{
		*row = get_next_line(*fd);
		while(empty_line(*row))
		{
			free(*row); 
			*row = get_next_line(*fd); 
		}
		if (!(*row) && !sc->map->map_present)
		{
			printf("Error! missing map\n");
			free_missing_map(sc, *row);
			exit(0);
		}
		if (*row)
		{
			sc->map->map_present = 1;
			sc->map->rows++;
		}
		else
			break;
		if (sc->map->rows == 1)
			sc->map->cols = count_map_cols(*row);
		free(*row);
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
	
	
	sc->map->room = (int **)malloc(sizeof(int *) * sc->map->rows);
	i = 0;
	while (i < sc->map->rows)
	{
		sc->map->room[i] = (int *)malloc(sizeof(int) * sc->map->cols);
		i++;
	}
	//printf("map rows = %d\n", rows);
	sc->map->mapX = sc->map->rows;
	//sc->rows = sc->map->rows;
	sc->map->mapY = sc->map->cols;
	sc->map->mapSize = sc->map->cols * sc->map->rows;
	close(*fd);
}

void	init_floor_ceiling_colors(t_scene *sc, char *row, int i)
{
	
	if (row[i] == 'F' && sc->f == 0)
	{
		sc->f = 1;
		get_rgb_values(sc, row, ++i, 'f');
	}
	else if (row[i] == 'C' && sc->c == 0)
	{
		sc->c = 1;
		get_rgb_values(sc, row, ++i, 'c');
	}
	else
	{
		printf("Error! Double key rows(floor/ceiling)\n");
		free_doublerow_ceilfloor(sc, row);
		exit(0);
	}
}


void	init_config_flags(t_scene *sc)
{
	sc->f = 0;
	sc->c = 0;
	sc->no = 0;
	sc->so = 0;
	sc->we = 0;
	sc->ea = 0;
	int i = 0;
	while (i < 3)
	{
		sc->floor[i] = 0;
		sc->ceil[i] = 0;
		i++;
	}
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


