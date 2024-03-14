#include "mlx_linux/mlx.h"
#include "cub3d.h"
#include <stdio.h>


void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}


void	put_pixel(t_scene *sc, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		i = sc->bpp - 8;
		pixel = sc->data_addr + (y * sc->line_width + x * sc->bpp / 8);
		while (i >= 0)
		{
			if (sc->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (sc->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}



void	draw_background(t_scene *sc)
{
	int	*image;
	int	i;

	ft_bzero(sc->data_addr, W_WIDTH * W_HEIGHT * (sc->bpp / 8));
	image = (int *)(sc->data_addr);
	i = 0;
	while (i < W_HEIGHT * W_WIDTH)
	{
		image[i] = 0x202020;
		i++;
	}
}

void	draw_player(t_scene *sc)
{
	//printf("posX = %d\n ", sc->player->posX);
	int	x;
	int	y;
	
	draw_background(sc);
	x = -(sc->player->size / 2);
	y = 0;
	while (y < sc->player->size)
	{
		x = -(sc->player->size / 2);
		while (x < sc->player->size / 2)
		{
			put_pixel(sc, sc->player->posX + x, sc->player->posY + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(sc->mlx, sc->win, sc->img, 0, 0);
}

int	key_press(int keycode, void *param)
{
	t_scene *sc = (t_scene *)param;
	//printf("keycode = %d\n ", keycode); 
	if (keycode == 119)
		sc->player->posY -= 5;
	else if (keycode == 97) // A
		sc->player->posX -= 5;
	else if (keycode == 100) // S
		sc->player->posX += 5;
	else if (keycode == 115) // D
		sc->player->posY += 5;
	
	draw_player(sc);

	return (0);
}

int	main()
{
	t_scene s;

	s.player = malloc(sizeof(t_player));
	s.player->posX = 400;
	s.player->posY = 300;
	s.player->size = 10;

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

	draw_player(&s); 
	mlx_hook(s.win, 2, 1L << 0, key_press, &s); 
	mlx_loop(s.mlx);

	return (0);
}
