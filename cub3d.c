
#include "cub3d.h"

void	init_scene(t_scene *sc)
{
	sc->player = malloc(sizeof(t_player));
	sc->player->posX = 400.0f;
	sc->player->posY = 300.0f;
	sc->player->size = 10;
	sc->player->angle = (3 * PI) / 2;
	sc->player->deltaX = cos(sc->player->angle) * 5;
	sc->player->deltaY = sin(sc->player->angle) * 5;
	sc->color = 0xFFFF00;
	
	sc->map = malloc(sizeof(t_map));
	sc->map->mapX = 8;
	sc->map->mapY = 8;
	sc->map->mapSize = sc->map->mapX * sc->map->mapY;
	sc->map->valIndex = 0;
	sc->map->values = malloc(sizeof(int) * sc->map->mapSize);
	
	sc->ray = malloc(sizeof(t_ray));
}

void put_player_on_map(t_scene *sc, char dir, int idx)
{
	
	if (dir == 'N')
		sc->player->angle = (3 * PI) / 2;
	else if (dir == 'S')
		sc->player->angle = PI / 2;
	else if (dir == 'W')
		sc->player->angle = PI;
	else if (dir == 'E')
		sc->player->angle = 0;
	sc->player->posY = (idx / sc->map->mapX) * sc->map->mapSize + (sc->map->mapSize / 2) - (sc->player->size / 2);
	sc->player->posX = (idx % sc->map->mapX) * sc->map->mapSize + (sc->map->mapSize / 2) + (sc->player->size / 2);
}


void	save_row_values(t_scene *sc, char *row)
{
	int i = 0;
	int j;
	int len = 0;
	j = sc->map->valIndex;
	
	while(row[i])
	{
		len++;
		i++;
	}
	//printf("num elementi riga = %d\n", len);
	i = 0;
	while (row[i] != '\n' && row[i] != '\0')
	{
		while (row[i] == ' ' || row[i] == '\t')
			i++;
		if (row[i] == '0')
			sc->map->values[j] = 0;
		else if (row[i] == '1')
			sc->map->values[j] = 1;
		else if (row[i] == 'N' || row[i] == 'S' || row[i] == 'W' || row[i] == 'E')
		{
			sc->map->values[j] = 0;
			put_player_on_map(sc, row[i], j);	
		}
		
		printf("%d", sc->map->values[j]);
		i++;
		j++;
	}
	printf("\n");
	sc->map->valIndex = j;
}


int	read_map(char *path, t_scene *sc)
{
	
	int	fd;
	char *row;
	
	fd = open(path, O_RDONLY);
	
	// faccio ciclo che legge tutte li righe della tabella
	// salvo ogni valore all' interno del mio array
	
	while (fd != -1)
	{
		row = get_next_line(fd);
	
		if (row)
		{
			//check_row_validity(row);
			save_row_values(sc, row);
		}
		else 
			break;
		free(row);
	}
	return (1);
}


int	main(int argc, char **argv)
{
	t_scene s;
	//int i = 0;
	
	
	
	if (argc == 2)
	{
		init_scene(&s);
		
		// IMPOSTA MAPPA
		/*while (i < s.map->mapSize)
		{
			if((i >= 0 && i < 8) || (i >= 56 && i < 64))
				s.map->values[i] = 1; 
			else if((i % 8) == 0 || (i+1) % 8 == 0)
				s.map->values[i] = 1;
			else if (i == 10 || i == 18 || i == 26 || i == 21)
				s.map->values[i] = 1;
			else
				s.map->values[i] = 0; 
			i++;
		}*/
		
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
		
		draw_map_2D(&s);
		draw_player(&s); 
		
		mlx_hook(s.win, 2, 1L << 0, key_press, &s); 
		mlx_loop(s.mlx);
	}
	
	else 
		printf("Error: invalid number of arguments-> Exit Program\n");

	return (0);
}
