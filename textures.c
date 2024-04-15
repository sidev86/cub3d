#include "cub3d.h"

void	load_image(t_scene *sc, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	img->img = mlx_xpm_file_to_image(sc->mlx, path, &img->img_w, &img->img_h);
	if (img->img == NULL)
	{
		printf("Error while loading texture! missing file or invalid path\n");
		exit(0);
	}
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
char *get_texture_path(char *row, int i)
{
	//int i = 0;
	int j = 0;
	char *path; 
	
	while (row[i] != ' ' && row[i] != '\t')
		i++;
	while (row[i] == ' ' || row[i] == '\t')
		i++;
	path = malloc(sizeof(char) * get_len(row, i));
	while (row[i] != ' ' && row[i] != '\t' && row[i] != '\n')
		path[j++] = row[i++];
	path[j] = '\0';
	return (path);
}

void	read_texture_file_data(t_scene *sc, char *row, int i)
{
	//char *row; 
	char *t_path;
	//int i = 0;
	//int j = 0;
	t_img img;
	
	
	t_path = get_texture_path(row, i);
	while(row[i] == ' ' || row[i] == '\t')
		i++;
	if (row[i] == 'N' && row[i + 1] == 'O' && sc->no == 0)
	{
		sc->no = 1;
		load_image(sc, sc->texture[1], t_path, &img);
	}
	else if (row[i] == 'S' && row[i + 1] == 'O' && sc->so == 0)
	{
		sc->so = 1;
		load_image(sc, sc->texture[0], t_path, &img);
	}
	else if (row[i] == 'E' && row[i + 1] == 'A' && sc->ea == 0)
	{
		sc->ea = 1;
		load_image(sc, sc->texture[2], t_path, &img);
	}
	else if (row[i] == 'W' && row[i + 1] == 'E' && sc->we == 0)
	{
		sc->we = 1;
		load_image(sc, sc->texture[3], t_path, &img);
	}
	else
	{ 
		printf("Error! Double key row(textures)\n");
		exit(0);
	}
	//free(row);
	free(t_path);
		
}

