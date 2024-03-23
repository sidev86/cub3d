#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define W_WIDTH 1280
#define W_HEIGHT 720
#define PI 3.1415926535
#define DGR 0.0174533

typedef struct s_player
{
	float posX;
	float posY;
	float deltaX;
	float deltaY;
	float angle;
	int size;
}	t_player;


typedef struct s_map
{
	int mapX; 
	int mapY;
	int mapSize;
	int *values;
}	t_map;


typedef struct	s_ray
{
	int mx;
	int my;
	int mp;
	
	int dof;
	float disH;
	float disV;
	float disT;
	float rx;
	float ry;
	float hx;
	float hy;
	float vx; 
	float vy;
	float cAng;
	float angle;
	float xo;
	float yo;
	float lineH;
	float lineO;
}	t_ray;

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int	bpp;
	int	endian;
	int	line_width;
	int	color;
	//int	player[3];
	t_player	*player;
	t_map		*map;
	t_ray		*ray;
}	t_scene;






//DRAW
void	put_pixel(t_scene *sc, int x, int y, int color);
void	draw_line(t_scene *sc, int *p1, int *p2);
void	draw_background(t_scene *sc);
void	draw_tile_map(t_scene *sc, int x, int y, int mapSize);
void	draw_map_2D(t_scene *sc);
void	draw_player(t_scene *sc);
void	draw_rays_3D(t_scene *sc);

//CONTROLS
int	key_press(int keycode, void *param);

//UTILS
void	ft_bzero(void *s, size_t n);


