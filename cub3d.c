
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

void	init_map(t_scene *sc, char *path)
{
	
	int fd;
	char *row;
	int rows;
	int cols;
	int i = 0;
	
	cols = 0;
	rows = 0;
	sc->map = malloc(sizeof(t_map));
	
	fd = open(path, O_RDONLY);
	while (fd != -1)
	{
		row = get_next_line(fd);
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
	close(fd);
}

void	init_scene(t_scene *sc, char *path)
{
	sc->color = 0xFFFF00;
	init_player(sc);
	init_map(sc, path);
	
	//init cam
	sc->cam = malloc(sizeof(t_camera));
	sc->cam->planeX = 0;
	sc->cam->planeY = 0.66f;

	sc->ray = malloc(sizeof(t_ray));
}

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
	sc->player->posX = (float)x + 0.2f;
	sc->player->posY = (float)y;
	
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


int	read_map(char *path, t_scene *sc)
{
	
	int	fd;
	int	num_row;
	char *row;
	
	num_row = 0; 
	fd = open(path, O_RDONLY);
	
	// faccio ciclo che legge tutte le righe della tabella
	// salvo ogni valore all' interno del mio array
	
	while (fd != -1)
	{
		row = get_next_line(fd);
	
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
	return (1);
}


int	main(int argc, char **argv)
{
	t_scene s;
	//int i = 0;
	
	if (argc == 2)
	{
		init_scene(&s, argv[1]);
		
		read_map(argv[1], &s);

		s.mlx = mlx_init();
		if (!s.mlx)
		{
			printf("Errore durante l'inizializzazione di mlx\n");
			return (1);
		}

		s.win = mlx_new_window(s.mlx, W_WIDTH, W_HEIGHT, "cub3d");
		if (!s.win)
		{
			printf("Errore durante la creazione della finestra\n");
			return (1);
		}

		s.img = mlx_new_image(s.mlx, W_WIDTH, W_HEIGHT);
		if (!s.img)
		{
			printf("Errore durante la creazione dell'immagine\n");
			return (1);
		}

		s.data_addr = mlx_get_data_addr(s.img, &(s.bpp), &(s.line_width), &(s.endian));
		if (!s.data_addr)
		{
			printf("Errore durante l'ottenimento dell'indirizzo dei dati dell'immagine\n");
			return (1);
		}
		
		//draw_map_2D(&s);
		draw_player(&s); 
		
		mlx_hook(s.win, 2, 1L << 0, key_press, &s); 
		mlx_loop(s.mlx);
	}
	
	else 
		printf("Error: invalid number of arguments-> Exit Program\n");

	return (0);
}
