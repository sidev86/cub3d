#include "cub3d.h"


void	set_player_north(t_scene *sc)
{
	sc->player->dirX = -1;
	sc->player->dirY = 0;
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;
}


void	set_player_south(t_scene *sc)
{
	sc->player->dirX = 1;
	sc->player->dirY = 0;
	sc->cam->planeX = 0;
	sc->cam->planeY = -0.66f;
}

void	set_player_west(t_scene *sc)
{
	sc->player->dirX = 0;
	sc->player->dirY = -1;
	sc->cam->planeX = -0.66f;
	sc->cam->planeY = 0;
}

void	set_player_east(t_scene *sc)
{
	sc->player->dirX = 0;
	sc->player->dirY = 1;
	sc->cam->planeX = 0.66f;
	sc->cam->planeY = 0;
}

void put_player_on_map(t_scene *sc, char dir, int x, int y)
{
	if (dir == 'N')
		set_player_north(sc);
	else if (dir == 'S')
		set_player_south(sc);
	else if (dir == 'W')
		set_player_west(sc);
	else if (dir == 'E')
		set_player_east(sc);
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
				free_invalid_map(sc);	
		}
		else
			free_invalid_map(sc);
	}
	else
		free_invalid_map(sc);
	
}

void	skip_empty_lines(char **row, int *fd)
{
	while (empty_line(*row))
	{
		free(*row);
		*row = get_next_line(*fd);
	}	
}


void read_config_lines(t_scene *sc, char **row, int *lines)
{
	int i;
	
	i = 0;
	while (*row[i] == ' ' || *row[i] == '\t')
		i++;
	if (*row[i] == 'F' || *row[i] == 'C')
	{
		init_floor_ceiling_colors(sc, *row, i);
		(*lines)++;
	}
	else if (is_texture_row(*row,i))
	{
		init_texture(sc, *row, i);
		(*lines)++;
	}
	else if (*lines < 6)
		free_wrong_key(sc, *row);
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

void	skip_config_lines(char **row, int *fd)
{
	int i; 
	
	i = 0;
	while (i < 6)
	{
		*row = get_next_line(*fd);
		skip_empty_lines(row, fd);
		if(*row)
		{
			free(*row);
			i++;
		}
	}
}

void	print_map(t_scene *sc)
{
	int i = 0; 
	int j = 0;
	
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
}


void	read_map(t_scene *sc, char *path)
{
	int	fd;
	int	num_row;
	char *row;
	
	num_row = 0; 
	fd = open(path, O_RDONLY);
	skip_config_lines(&row, &fd);
	while (fd != -1)
	{
		row = get_next_line(fd);
		while(empty_line(row))
		{
			free(row); 
			row = get_next_line(fd); 
		}
		if (row)
			save_map_row_values(sc, row, num_row);
		else 
			break;
		num_row++;
		free(row);
	}
	print_map(sc);
}






