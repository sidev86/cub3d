#include "cub3d.h"

void	init_player(t_scene *sc)
{
	sc->player = malloc(sizeof(t_player));
	sc->player->posX = 2.0f;
	sc->player->posY = 7.0f;
	sc->player->dirX = -1;
	sc->player->dirY = 0;
	sc->player->size = 10;
	sc->player->angle = (3 * PI) / 2;
	sc->player->deltaX = cos(sc->player->angle) * 5;
	sc->player->deltaY = sin(sc->player->angle) * 5;
}

void	init_texture(t_scene *sc, char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		printf("Error while opening file\n");
	sc->texture = (int **)malloc(sizeof(int *) * 8);
	if (!sc->texture)
		printf("Error in texture allocation\n");
	texture_cycle(sc);
	read_texture_file_data(sc, fd);
	//load_texture(sc);
}

void	init_map(t_scene *sc, int *fd)
{
	
	char *row;
	int rows;
	int cols;
	int i = 0;
	
	cols = 0;
	rows = 0;
	sc->map = malloc(sizeof(t_map));
	
	
	while (*fd != -1)
	{
		row = get_next_line(*fd);
		while(empty_line(row))
		{
			free(row); 
			row = get_next_line(*fd); 
		}
		if (row)
			rows++;
		else
			break;
		if (rows == 1)
			cols = count_map_cols(row);
	}
	
	sc->map->room = (int **)malloc(sizeof(int *) * rows);
	while (i < rows)
	{
		sc->map->room[i] = (int *)malloc(sizeof(int) * cols);
		i++;
	}
	sc->map->mapX = rows;
	sc->map->mapY = cols;
	sc->map->mapSize = cols * rows;
	close(*fd);
}

void	init_scene(t_scene *sc, char *path)
{
	int fd;
	sc->color = 0xFFFF00;
	sc->re_buf = 0;
	init_player(sc);
	init_texture(sc, path, &fd);
	init_map(sc, &fd);
	clear_buffer(sc);
	
	//init cam
	sc->cam = malloc(sizeof(t_camera));
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;
	sc->cam->x = 0;

	sc->ray = malloc(sizeof(t_ray));
}


