#include "cub3d.h"

void put_player_on_map(t_scene *sc, char dir, int x, int y)
{
	if (dir == 'N')
	{
		sc->player->dirX = -1;
		sc->player->dirY = 0;
		sc->cam->planeX = 0;
		sc->cam->planeY = 0.66f;
		//sc->player->angle = (3 * PI) / 2;
	}
	else if (dir == 'S')
	{
		sc->player->dirX = 1;
		sc->player->dirY = 0;
		sc->cam->planeX = 0;
		sc->cam->planeY = -0.66f;
		//sc->player->angle = PI / 2;
	}
	else if (dir == 'W')
	{
		sc->player->dirX = 0;
		sc->player->dirY = -1;
		sc->cam->planeX = -0.66f;
		sc->cam->planeY = 0;
		//sc->player->angle = PI;
	}
	else if (dir == 'E')
	{
		sc->player->dirX = 0;
		sc->player->dirY = 1;
		sc->cam->planeX = 0.66f;
		sc->cam->planeY = 0;
		//sc->player->angle = 0;
	}
	sc->player->posX = (double)x + 0.2f;
	sc->player->posY = (double)y;
	
}

int	count_map_cols(char *r)
{
	int i;
	int cols;
	
	i = 0;
	cols = 0;
	while (r[i] != '\0' && r[i] != '\n')
	{
		while (r[i] == ' ' || r[i] == '\t')
			i++; 
		if (r[i] == '0' || r[i] == '1' || r[i] == 'N' || r[i] == 'S' || r[i] == 'E' || r[i] == 'W')
			cols++;
		i++;
	}
	return (cols);
}

void	save_map_row_values(t_scene *sc, char *row, int x)
{
	
	int y = 0;
	
	while (y < sc->map->mapY)
	{
		while (row[y] == ' ' || row[y] == '\t')
			y++;
		if (row[y] == '0')
			sc->map->room[x][y] = 0;
		else if (row[y] == '1')
			sc->map->room[x][y] = 1;
		else if (row[y] == 'N' || row[y] == 'S' || row[y] == 'W' || row[y] == 'E')
		{
			sc->map->room[x][y] = 0;
			put_player_on_map(sc, row[y], x, y);
		}
		y++;
	}
}


int	is_texture_row(char *row, int i)
{
	if (row[i] == 'N' && row[i + 1] == 'O')
		return(1);
	else if (row[i] == 'S' && row[i + 1] == 'O')
		return(1);
	else if (row[i] == 'E' && row[i + 1] == 'A')
		return(1);
	else if (row[i] == 'W' && row[i + 1] == 'E')
		return(1);
	else
		return(0);
}

void	check_file_extension(t_scene *sc, char *path)
{
	int i = 0;
	
	while(path[i] != '.' && path[i])
		i++;
	if (path[i] == '.')
	{
		if (path[i+1] == 'c' && path[i+2] == 'u' && path[i+3] == 'b')
		{
			if (path[i+4] != '\0' && path[i+4] != ' ')
			{
				perror("Error! Invalid file map format (.cub extension needed)");
				free_invalid_map(sc);
				exit(0);
			}		
		}
		else
		{
			perror("Error! Invalid file map format (.cub extension needed)\n");
			free_invalid_map(sc);
			exit(0);
		}
	}
	else
	{
		perror("Error! Invalid file map format (.cub extension needed)\n");
		free_invalid_map(sc);
		exit(0);
	}
}

void 	read_data_before_map(t_scene *sc, char *path, int *fd)
{
	int i;
	char *row;
	int lines = 0;
	
	i = 0;
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		printf("Error while opening file\n");
	check_file_extension(sc, path);
	while (*fd != -1)
	{
		i = 0;
		row = get_next_line(*fd);
		while (empty_line(row))
		{
			free(row);
			row = get_next_line(*fd);
		}
		if (!row)
		{
			printf("Error in data file read: empty file\n");
			free_empty_file(sc);
			exit(0);
		}
		while (row[i] == ' ' || row[i] == '\t')
			i++;
		if (row[i] == 'F' || row[i] == 'C')
		{
			init_floor_ceiling_colors(sc, row, i);
			lines++;
		}
		else if (is_texture_row(row,i))
		{
			init_texture(sc, row, i);
			lines++;
		}
		else if (lines < 6)
		{
			printf("Error in data file read: missing or wrong key row in texture and/or floor-ceiling config\n");
			free_wrong_key(sc, row);
			exit(0);
		}
		free(row);
		if (lines == 6)
			break;	
	}	
}



int	read_map(t_scene *sc, char *path)
{
	
	int	fd;
	int	num_row;
	char *row;
	int i;
	int j;
	
	i = 0;
	
	num_row = 0; 
	// faccio ciclo che legge tutte le righe della tabella
	// salvo ogni valore all' interno del mio array
	fd = open(path, O_RDONLY);
	// skippo righe texture e floor/ceiling
	while (i < 6)
	{
		row = get_next_line(fd);
		while(empty_line(row))
		{
			free(row); 
			row = get_next_line(fd); 
		}
		if(row)
		{
			free(row);
			i++;
		}
	}
	
	while (fd != -1)
	{
		row = get_next_line(fd);
		while(empty_line(row))
		{
			free(row); 
			row = get_next_line(fd); 
		}
		if (row)
		{
			//check_row_validity(row);
			save_map_row_values(sc, row, num_row);
		}
		else 
			break;
		num_row++;
		free(row);
	}
	
	i = 0; 
	j = 0;
	
	while (i < sc->map->mapX)
	{
		j = 0;
		while(j < sc->map->mapY)
		{
			printf("%d", sc->map->room[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (1);
}






