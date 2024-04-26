#include "cub3d.h"

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

int	scene_loop(t_scene *sc)
{
	calculate_rays(sc);
	draw_scene(sc);
	//draw_map_2D(sc);
	//draw_player(sc); 
	return (1);
}

void	init_mlx(t_scene *sc)
{
	if (!sc->mlx)
	{
		printf("Errore durante l'inizializzazione di mlx\n");
		exit (1);
	}

	sc->win = mlx_new_window(sc->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	if (!sc->win)
	{
		printf("Errore durante la creazione della finestra\n");
		exit (1);
	}

	sc->img.img = mlx_new_image(sc->mlx, W_WIDTH, W_HEIGHT);
	if (!sc->img.img)
	{
		printf("Errore durante la creazione dell'immagine\n");
		exit (1);
	}

	sc->img.data_addr = (int *)mlx_get_data_addr(sc->img.img, &(sc->img.bpp), &(sc->img.line_width), &(sc->img.endian));
	if (!sc->img.data_addr)
	{
		printf("Errore durante l'ottenimento dell'indirizzo dei dati dell'immagine\n");
		exit (1);
	}
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
		check_map_validity(&s);
		init_mlx(&s);
		mlx_loop_hook(s.mlx, &scene_loop, &s);
		mlx_hook(s.win, 2, 1L << 0, key_press, &s); 
		mlx_hook(s.win, 17, 0, &close_window, &s);
		mlx_loop(s.mlx);
	}
	
	else 
		printf("Error: invalid number of arguments-> Exit Program\n");
	return (0);
}
