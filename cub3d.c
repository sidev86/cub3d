#include "cub3d.h"

void	clear_buffer(t_scene *sc)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	
	while (x < W_HEIGHT)
	{
		y = 0;
		while(y < W_WIDTH)
		{
			sc->buff[x][y] = 0;
			y++;
		}
		x++;
	}
}

void	draw_scene(t_scene *sc)
{
	int x; 
	int y; 
	
	x = 0;
	y = 0;
	while (y < W_HEIGHT)
	{
		while(x < W_WIDTH)
		{
		
			sc->img.data_addr[y * W_WIDTH + x] = sc->buff[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(sc->mlx, sc->win, sc->img.img, 0, 0);
}

int scene_loop(t_scene *sc)
{
	calculate_rays(sc);
	draw_scene(sc);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene s;
	//int i = 0;
	
	if (argc == 2)
	{
		s.mlx = mlx_init();
		init_scene(&s, argv[1]);
		
		read_map(&s, argv[1]);

		
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

		s.img.img = mlx_new_image(s.mlx, W_WIDTH, W_HEIGHT);
		if (!s.img.img)
		{
			printf("Errore durante la creazione dell'immagine\n");
			return (1);
		}

		s.img.data_addr = (int *)mlx_get_data_addr(s.img.img, &(s.img.bpp), &(s.img.line_width), &(s.img.endian));
		if (!s.img.data_addr)
		{
			printf("Errore durante l'ottenimento dell'indirizzo dei dati dell'immagine\n");
			return (1);
		}
		
		//draw_map_2D(&s);
		//draw_player(&s); 
		
		mlx_loop_hook(s.mlx, &scene_loop, &s);
		mlx_hook(s.win, 2, 1L << 0, key_press, &s); 
		mlx_loop(s.mlx);
	}
	
	else 
		printf("Error: invalid number of arguments-> Exit Program\n");

	return (0);
}
