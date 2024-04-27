#include "cub3d.h"

#define VISITED 'x'

static void flood_fill(t_scene *sc, int x, int y)
{
	if (x < 0 || x >= sc->map->rows || y < 0 || y >= sc->map->cols)
		free_map_validity_check(sc, 'o');
	if (sc->map->room[x][y] == '1' || sc->map->room[x][y] == VISITED)
		return;
	if (sc->map->room[x][y] != '0' && sc->map->room[x][y] != 'E' && sc->map->room[x][y] != 'N' && sc->map->room[x][y] != 'S' && sc->map->room[x][y] != 'W')
		free_map_validity_check(sc, 'o');
	if (sc->map->room[x][y] == '0' && (sc->map->room[x][y] != 'E' || sc->map->room[x][y] != 'N' || sc->map->room[x][y] != 'S' || sc->map->room[x][y] != 'W'))
		sc->map->room[x][y] = VISITED;

	// ricorsivamente controlla i vicini
	
	flood_fill(sc, x + 1, y);
	flood_fill(sc, x - 1, y);
	flood_fill(sc, x, y + 1);
	flood_fill(sc, x, y - 1);
}

static void border_check1(t_scene *sc, int rows, int cols, int j)
{
	printf("j: %d\n", j);
	printf("rows: %d\n", rows);
	printf("cols: %d\n", cols);
	while (j < cols)
	{
		if (sc->map->room[rows][j] != '1' && sc->map->room[rows][j] != '2')
			free_map_validity_check(sc, 'o');
		j++;
	}
	rows = sc->map->rows - 1;
	cols = sc->map->cols;
	printf("cols = %d\n", cols);
	j = 0;
	while (j < cols)
	{
		if (sc->map->room[rows][j] != '1' && sc->map->room[rows][j] != '2')
			free_map_validity_check(sc, 'o');
		j++;
	}
}

static void border_check(t_scene *sc)
{
	int	rows;
	int	cols;
	int	j;

	rows = 0;
	cols = sc->map->cols;
	printf("cols: %d\n", cols);
	j = 0;
	border_check1(sc, rows, cols, j);
}

static void count_players(t_scene *sc, int i, int j, int player_count)
{
	while (i < sc->map->rows)
	{
		j = 0;
		while (j < sc->map->cols)
		{
			if (sc->map->room[i][j] == 'N' || sc->map->room[i][j] == 'S'
				|| sc->map->room[i][j] == 'E' || sc->map->room[i][j] == 'W')
			{
				sc->map->room[i][j] = '0';
				player_count++;
				if (player_count > 1)
					free_map_validity_check(sc, 'p');
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)	
		free_map_validity_check(sc, 'n');	
}

static void check_player(t_scene *sc)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	j = 0;
	count_players(sc, i, j, player_count);
}

void check_map_validity(t_scene *sc)
{
    int		i;
    int		j;

    printf("Mappa dopo la correzione:\n");
    print_map(sc);
    border_check(sc);
    check_player(sc);
    i = 0;
    while (i < sc->map->rows)
    {
        j = 0;
        while (j < sc->map->cols)
        {
            if (sc->map->room[i][j] == '0' || sc->map->room[i][j] == 'E' || sc->map->room[i][j] == 'N' || sc->map->room[i][j] == 'S' || sc->map->room[i][j] == 'W')
                flood_fill(sc, i, j);
            j++;
        }
        i++;
    }
    printf("\n");
    print_map(sc);
    printf("\n");
    i = 0;
    while (i < sc->map->rows)
    {
        j = 0;
        while (j < sc->map->cols)
        {
            if (sc->map->room[i][j] == 'x')
                sc->map->room[i][j] = '0';
            j++;
        }
        i++;
    }
    print_map(sc);
    printf("La mappa e' corretta\n");
}
