#include "cub3d.h"

static void free_texture(t_scene *sc)
{
	int i;
	i = 0;
	while (i < 8)
	{
		free(sc->texture[i]);
		i++;

	}
	free(sc->texture);
}

void free_doublerow_ceilfloor(t_scene *sc, char *row)
{
	printf("Error in file data read! Missing color\n");
	printf("Error in file data read! invalid rgb color values\n");
	free_texture(sc);
	free(sc->player);
	free(row);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);

}

void free_doublerow_texture(t_scene *sc, char *row, char *path)
{
	printf("Error! Double key row(textures)\n");
	free_texture(sc);
	free(sc->player);
	free(row);
	free(path);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void free_wrong_key(t_scene *sc, char *row)
{
	printf("Error in data file read: missing or wrong key row in texture and/or floor-ceiling config\n");
	if (sc->text_init)
		free_texture(sc);
	free(row);
	free(sc->player);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void free_missing_map(t_scene *sc, char *row)
{
	free_texture(sc);
	free(sc->player);
	free(sc->map);
	free(row);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
}


void free_empty_file(t_scene *sc)
{
	printf("Error in data file read: empty file\n");
	mlx_destroy_display(sc->mlx);
	free(sc->player);
	free(sc->mlx);
	exit(0);
}


void free_invalid_map(t_scene *sc)
{
	perror("Error! Invalid file map format (.cub extension needed)");
	free(sc->player);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}


void free_missing_file(t_scene *sc, char *row, char *path)
{
	free_texture(sc);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	free(sc->player);
	free(row);
	free(path);
}

