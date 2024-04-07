#include "cub3d.h"

void	put_pixel(t_scene *sc, int x, int y, int color)
{
	int	*pixel;
	int		i;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		i = sc->img.bpp - 8;
		pixel = sc->img.data_addr + (y * sc->img.line_width + x * sc->img.bpp / 8);
		while (i >= 0)
		{
			if (sc->img.endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (sc->img.bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}


void	draw_background(t_scene *sc)
{
	int	*image;
	int	i;

	ft_bzero(sc->img.data_addr, W_WIDTH * W_HEIGHT * (sc->img.bpp / 8));
	image = (int *)(sc->img.data_addr);
	i = 0;
	while (i < W_HEIGHT * W_WIDTH)
	{
		image[i] = 0x202020;
		i++;
	}
}


void draw_tile_map(t_scene *sc, int x, int y, int mapSize)
{
	int xLimit = x + mapSize - 1;
	int yLimit = y + mapSize - 1;
	int xPrevious = x;
	
	while (y < yLimit)
	{
		x = xPrevious;
		while (x < xLimit)
		{
			put_pixel(sc, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void draw_map_2D(t_scene *sc)
{
	int x, y, x0, y0;
	

	draw_background(sc);
	for (x = 0; x < sc->map->mapX; x++)
	{
		for (y = 0; y < sc->map->mapY; y++)
		{
			if (sc->map->room[x][y] == 1)
			{
				x0 = x * sc->map->mapSize;
				y0 = y * sc->map->mapSize;
				draw_tile_map(sc, x0, y0, sc->map->mapSize);
			}
			
			//put_pixel(sc, x0, y0,  color);
			//put_pixel(sc, x0 + 63, y0, color);
			//put_pixel(sc, x0, y0 + 63, color);
			//put_pixel(sc, x0 + 63, y0 + 63, color);
			
		}
	}
	mlx_put_image_to_window(sc->mlx, sc->win, sc->img.img, 0, 0);
}

void	draw_player(t_scene *sc)
{
	//printf("posX = %d\n ", sc->player->posX);
	int	x;
	int	y;
	//int	p1[2]; 
	//int	p2[2];
	draw_background(sc);
	x = -(sc->player->size / 2);
	y = 0;
	while (y < sc->player->size)
	{
		x = -(sc->player->size / 2);
		while (x < sc->player->size / 2)
		{
			put_pixel(sc, (int)(sc->player->posX) + x, (int)(sc->player->posY) + y, 0xFFFF00);
			x++;
		}
		y++;
	}
	// disegna linea direzione POV
	//draw_line(sc, p1, p2);
	calculate_rays(sc);
	mlx_put_image_to_window(sc->mlx, sc->win, sc->img.img, 0, 0);
}
