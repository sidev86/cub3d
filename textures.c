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

int	get_len(char *row, int i)
{
	int len;
	
	len = 0;
	while(row[i] != ' ' && row[i] != '\t' && row[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);

}
char *get_texture_path(char *row)
{
	int i = 0;
	int j = 0;
	char *path; 
	
	while (row[i] != ' ')
		i++;
	while (row[i] == ' ')
		i++;
	path = malloc(sizeof(char) * get_len(row, i));
	while (row[i] != ' ' && row[i] != '\t' && row[i] != '\n')
		path[j++] = row[i++];
	path[j] = '\0';
	return (path);
}

void	read_texture_file_data(t_scene *sc, int *fd)
{
	char *row; 
	char *t_path;
	int i = 0;
	int j = 0;
	t_img img;
	
	
	while (*fd != -1 && i < 4)
	{
		row = get_next_line(*fd);
		j = 0;
		if (row)
		{
			t_path = get_texture_path(row);
			while(row[j] == ' ' || row[j] == '\t')
				j++;
			if (row[j] == 'N' && row[j + 1] == 'O')
				load_image(sc, sc->texture[1], t_path, &img);
			else if (row[j] == 'S' && row[j + 1] == 'O')
				load_image(sc, sc->texture[0], t_path, &img);
			else if (row[j] == 'E' && row[j + 1] == 'A')
				load_image(sc, sc->texture[2], t_path, &img);
			else if (row[j] == 'W' && row[j + 1] == 'E')
				load_image(sc, sc->texture[3], t_path, &img);
			else 
				printf("error while loading texture data\n");
			free(row);
			free(t_path);
		}
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
