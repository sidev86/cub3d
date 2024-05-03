#include "cub3d.h"

void	free_texture(t_scene *sc)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(sc->texture[i]);
		i++;
	}
	free(sc->texture);
}

void	free_doublerow_ceilfloor(t_scene *sc, char *row, char message)
{
	if (message == 'm')
		perror("Error\nMissing rgb ceil/floor color\n");
	else if (message == 'v')
		perror("Error\nInvalid rgb color values\n");
	else
		perror("Error\nDouble key rows(floor/ceiling)\n");
	if (sc->text_init)
		free_texture(sc);
	free(sc->player);
	free(row);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_doublerow_texture(t_scene *sc, char *row, char *path, char message)
{
	if (message == 'd')
		perror("Error\nDouble key row(textures)\n");
	else if (message == 'w')
		perror("Error\nMissing attributes on row\n");
	free_texture(sc);
	free(sc->player);
	free(row);
	free(path);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_wrong_key(t_scene *sc, char *row)
{
	perror("Error\nMissing or wrong key row\n");
	if (sc->text_init)
		free_texture(sc);
	free(row);
	free(sc->player);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_missing_map(t_scene *sc, char *row)
{
	perror("Error\nMissing map\n");
	free_texture(sc);
	free(sc->player);
	free(sc->map);
	free(row);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}
