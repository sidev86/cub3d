#include "cub3d.h"

void	load_image(t_scene *sc, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	img->img = mlx_xpm_file_to_image(sc->mlx, path, &img->img_w, &img->img_h);
	img->data_addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_width, &img->endian);
	while (y < img->img_h)
	{
		x = 0;
		while (x < img->img_w)
		{
			texture[img->img_w * y + x] = img->data_addr[img->img_w * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(sc->mlx, img->img);
}

void texture_cycle(t_scene *sc)
{

	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < 8)
	{
		sc->texture[i] = (int *)malloc(sizeof(int) * (T_WIDTH * T_HEIGHT));
		if (!sc->texture[i])
			printf("Error in texture allocation\n");
		while (j < T_WIDTH * T_HEIGHT)
		{
			sc->texture[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
}

void	load_texture(t_scene *sc)
{
	t_img	img;
	load_image(sc, sc->texture[0], "textures/eagle.xpm", &img);
	load_image(sc, sc->texture[1], "textures/redbrick.xpm", &img);
	load_image(sc, sc->texture[2], "textures/purplestone.xpm", &img);
	load_image(sc, sc->texture[3], "textures/greystone.xpm", &img);
	load_image(sc, sc->texture[4], "textures/bluestone.xpm", &img);
	load_image(sc, sc->texture[5], "textures/mossy.xpm", &img);
	load_image(sc, sc->texture[6], "textures/wood.xpm", &img);
	load_image(sc, sc->texture[7], "textures/colorstone.xpm", &img);
}
