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




int	empty_line(char *row)
{
	int i;
	
	i = 0;
	if (!row)
		return (0);
	while (row[i] == ' ' || row[i] == '\t')
		i++;
	if (row[i] == '\n')
		return(1);
	else
		return(0);
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
	while (i++ < 4)
		row = get_next_line(fd);
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






