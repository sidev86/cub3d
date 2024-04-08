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
		free(row);
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

void	get_rgb_values(t_scene *sc, char *row, int i, char type)
{
	int t = 0; 
	int j = 0;
	char rgb_str[3];
	while (t < 3)
	{
		while (row[i] == ' ' || row[i] == '\t')
			i++;
		while (row[i] != ',' && row[i] != '\n' && row[i] != '\0')
			rgb_str[j++] = row[i++];
		i++;
		if (type == 'f')
			sc->floor[t] = atoi(rgb_str);
		else if (type == 'c')
			sc->ceil[t] = atoi(rgb_str);
		j = 0;
		while (j < 3)
			rgb_str[j++] = 0;
		j = 0;
		t++;
	}

}

void	save_floor_ceiling_colors(t_scene *sc, char *row)
{
	int i = 0; 
	
	if (row[i] == 'F')
		get_rgb_values(sc, row, ++i, 'f');
	else if (row[i] == 'C')
		get_rgb_values(sc, row, ++i, 'c');
}

void	init_floor_ceiling(t_scene *sc, int fd)
{
	char *row;
	int i = 0;
	int lines = 0;
	
	while (fd != -1)
	{
		i = 0;
		row = get_next_line(fd);
		while (empty_line(row))
		{
			free(row);
			row = get_next_line(fd);
		}
		if (row[i] == 'F' || row[i] == 'C')
		{
			save_floor_ceiling_colors(sc, row);
			lines++;
		}
		free(row);
		if (lines == 2)
			break;
	}

}


void	init_scene(t_scene *sc, char *path)
{
	int fd;
	sc->color = 0xFFFF00;
	sc->re_buf = 0;
	init_player(sc);
	init_texture(sc, path, &fd);
	init_floor_ceiling(sc, fd);
	init_map(sc, &fd);
	clear_buffer(sc);
	
	//init cam
	sc->cam = malloc(sizeof(t_camera));
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;
	sc->cam->x = 0;

	sc->ray = malloc(sizeof(t_ray));
}


