#include "mlx_linux/mlx.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#define W_WIDTH 1024
#define W_HEIGHT 768
#define PI 3.1415926535
#define DGR 0.0174533

typedef struct s_player
{
	float posX;
	float posY;
	float dirX; 
	float dirY;
	float deltaX;
	float deltaY;
	//float planeX; 
	//float planeY;
	float angle;
	int size;
}	t_player;


typedef struct s_map
{
	int mapX; 
	int mapY;
	int mapSize;
	int **room;
	int valIndex;
}	t_map;


typedef struct	s_ray
{
	float dirX;
	float dirY;
	float sideDistX;
	float sideDistY;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
}	t_ray;

typedef struct s_camera
{
	float x;
	float y;
	float planeX;
	float planeY;
}	t_camera;

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
	t_camera	*cam;
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


