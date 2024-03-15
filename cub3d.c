
#include "cub3d.h"
#include <stdio.h>



int	main()
{
	t_scene s;
	int i = 0;
	
	
	s.player = malloc(sizeof(t_player));
	s.player->posX = 400;
	s.player->posY = 300;
	s.player->size = 10;
	
	s.map = malloc(sizeof(t_map));
	s.map->mapX = 8;
	s.map->mapY = 8;
	s.map->mapSize = 64;
	s.map->values = malloc(sizeof(int) * s.map->mapSize);
	
	
	while (i < s.map->mapSize)
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
	}

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

	return (0);
}
