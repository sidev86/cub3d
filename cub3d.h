#include "mlx_linux/mlx.h"
#include <stdlib.h>

#define W_WIDTH 800
#define W_HEIGHT 600

typedef struct s_player
{
	int posX;
	int posY;
	int size;
}	t_player;


typedef struct s_map
{
	int mapX; 
	int mapY;
	int mapSize;
	int *values;
}	t_map;


typedef struct s_scene
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int	bpp;
	int	endian;
	int	line_width;
	//int	player[3];
	t_player	*player;
	t_map		*map;
}	t_scene;




//DRAW
void	put_pixel(t_scene *sc, int x, int y, int color);
void	draw_background(t_scene *sc);
void	draw_tile_map(t_scene *sc, int x, int y, int mapSize);
void	draw_map_2D(t_scene *sc);
void	draw_player(t_scene *sc);

//CONTROLS
int	key_press(int keycode, void *param);

//UTILS
void	ft_bzero(void *s, size_t n);


