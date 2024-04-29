#include "cub3d.h"

void	free_empty_file(t_scene *sc)
{
	perror("Error in data file read: empty file\n");
	mlx_destroy_display(sc->mlx);
	free(sc->player);
	free(sc->mlx);
	exit(0);
}

void	free_invalid_map(t_scene *sc, char message)
{
	if (message == 'm')
		perror("Error! Invalid file map format (.cub extension needed)");
	else if (message == 'f')
		perror("Error while opening file\n");
	free(sc->player);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_map_wrong(t_scene *sc, char *row)
{
	int	i;

	i = 0;
	perror("Error! Invalid map\n");
	while (i < sc->map->rows)
		free(sc->map->room[i++]);
	free(sc->map->room);
	free(sc->map);
	free_texture(sc);
	free(sc->cam);
	free(sc->player);
	free(sc->ray);
	free(row);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_map_validity_check(t_scene *sc, char message)
{
	int	i;

	i = 0;
	if (message == 'o')
		perror("Map check error, not completely surronded by walls\n");
	else if (message == 'n')
		perror("Map check error! Missing player position\n");
	else if (message == 'p')
		perror("Map check error! More than one player position on map\n");
	while (i < sc->map->rows)
		free(sc->map->room[i++]);
	free(sc->map->room);
	free(sc->map);
	free_texture(sc);
	free(sc->cam);
	free(sc->player);
	free(sc->ray);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}

void	free_missing_file(t_scene *sc, char *row, char *path)
{
	if (sc->text_init)
		free_texture(sc);
	free(sc->player);
	free(row);
	free(path);
	mlx_destroy_display(sc->mlx);
	free(sc->mlx);
	exit(0);
}
