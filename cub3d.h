#include "mlx_linux/mlx.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#define W_WIDTH 640
#define W_HEIGHT 480
#define T_WIDTH 64
#define T_HEIGHT 64
#define PI 3.1415926535
#define DGR 0.0174533

typedef struct s_player
{
	double posX;
	double posY;
	double dirX; 
	double dirY;
	double deltaX;
	double deltaY;
	double angle;
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
	double dirX;
	double dirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
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
	double x;
	double y;
	double planeX;
	double planeY;
}	t_camera;


typedef struct	s_img
{
	void	*img;
	int		*data_addr;

	int		line_width;
	int		bpp;
	int		endian;
	int		img_w;
	int		img_h;
}				t_img;

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	
	int	color;
	int	buff[W_HEIGHT][W_WIDTH];
	int	**texture;
	int texX; 
	int texY;
	int re_buf;
	int init_tex;
	unsigned int floor[3];
	unsigned int ceil[3];
	double wallX;
	double step;
	double texPos;
	
	t_player	*player;
	t_map		*map;
	t_ray		*ray;
	t_camera	*cam;
	t_img		img;
}	t_scene;


//INIT
void	init_scene(t_scene *sc, char *path);


//DRAW
void	put_pixel(t_scene *sc, int x, int y, int color);
void	draw_line(t_scene *sc, int *p1, int *p2);
void	draw_background(t_scene *sc);
void	draw_tile_map(t_scene *sc, int x, int y, int mapSize);
void	draw_map_2D(t_scene *sc);
void	draw_player(t_scene *sc);
void	calculate_rays(t_scene *sc);

//MAP
int	read_map(t_scene *sc, char *path);
int	count_map_cols(char *r);
int	empty_line(char *row);

//TEXTURES
void	texture_cycle(t_scene *sc);
void	read_texture_file_data(t_scene *sc, char *row);

//CONTROLS
int	key_press(int keycode, void *param);

//UTILS
void	ft_bzero(void *s, size_t n);


void	clear_buffer(t_scene *sc);
int	scene_loop(t_scene *sc);
int	close_window(void *param);


