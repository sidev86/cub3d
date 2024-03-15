#include "cub3d.h"

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
	for (y = 0; y < sc->map->mapY; y++)
	{
		for (x = 0; x < sc->map->mapX; x++)
		{
			if (sc->map->values[y * (sc->map->mapX) + x] == 1)
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
	//mlx_put_image_to_window(sc->mlx, sc->win, sc->img, 0, 0);
}



void	draw_player(t_scene *sc)
{
	//printf("posX = %d\n ", sc->player->posX);
	int	x;
	int	y;
	
	//draw_background(sc);
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
