#include "cub3d.h"


unsigned int rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


int no_value(char *row, int i)
{
	int value = 0;
	
	while (row[i] == ' ' || row[i] == '\t' || row[i] == '-')
		i++;
	
	while(row[i] != ',')
	{
		if(row[i] >= '0' && row[i] <= '9')
			value = 1;
		i--;
	}
	if (!value)
		return(1);
	return(0);
}

int	missing_commas(char *row)
{
	int	i = 0;
	int commas = 0;
	while (row[i] != '\n')
	{
		if (row[i] == ',')
			commas++;
		i++;
	}
	if (commas < 2)
		return(1);
	return(0);
}

void	get_rgb_values(t_scene *sc, char *row, int i, char type)
{
	int t = 0; 
	int j = 0;
	char rgb_str[3];
	while (t < 3)
	{
		while (row[i] == ' ' || row[i] == '\t')
			i++;
		while (row[i] != ',' && row[i] != '\n' && row[i] != '\0')
			rgb_str[j++] = row[i++];
		i++;
		if (no_value(row, i) || missing_commas(row))
		{
			printf("Error in file data read! Missing color\n");
			exit(0);
		}
		if (type == 'f')
			sc->floor[t] = atoi(rgb_str);
		else if (type == 'c')
			sc->ceil[t] = atoi(rgb_str);
		if (sc->floor[t] < 0 || sc->ceil[t] < 0 || sc->floor[t] > 255 || sc->ceil[t] > 255)
		{
			printf("Error in file data read! invalid rgb color values\n");
			exit(0);
		}
		j = 0;
		while (j < 3)
			rgb_str[j++] = 0;
		j = 0;
		t++;
	}

}

void	draw_floor_ceiling(t_scene *sc)
{
	int x = 0; 
	int y = 0; 
	unsigned int floor_hex = rgb_to_hex(sc->floor[0], sc->floor[1], sc->floor[2]);
	unsigned int ceil_hex = rgb_to_hex(sc->ceil[0], sc->ceil[1], sc->ceil[2]);
	while(y < W_HEIGHT)
	{
		while(x < W_WIDTH)
		{
			sc->buff[y][x] = floor_hex;
			sc->buff[W_HEIGHT - y -1][x] = ceil_hex;
			x++;
		}
		x = 0; 
		y++;
	
	}

}
