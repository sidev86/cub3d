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
	double oldDirX; 
	double oldPlaneX;
	double deltaX;
	double deltaY;
	double angle;
	double moveSpeed;
	double rotSpeed;
	int size;
}	t_player;


typedef struct s_map
{
	int mapX; 
	int mapY;
	int mapSize;
	char **room;
	int rows;
	int cols; 
	int map_present;
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
	int floor[3];
	int ceil[3];
	int f;
	int c;
	int no; 
	int so; 
	int we;
	int ea;
	int text_init;
	int rows;
	double wallX;
	double step;
	double texPos;
	char *t_path;
	
	t_player	*player;
	t_map		*map;
	t_ray		*ray;
	t_camera	*cam;
	t_img		img;
}	t_scene;


void check_map_validity(t_scene *sc);
//INIT
void	init_scene(t_scene *sc, char *path);
void	init_floor_ceiling_colors(t_scene *sc, char *row, int i);
void	init_texture(t_scene *sc,char *row, int i);
void	init_floor_ceiling_colors(t_scene *sc, char *row, int i);
void	set_initial_ray_data(t_scene *sc, int x);

//DRAW
void	put_pixel(t_scene *sc, int x, int y, int color);
void	draw_line(t_scene *sc, int *p1, int *p2);
void	draw_background(t_scene *sc);
void	draw_tile_map(t_scene *sc, int x, int y, int mapSize);
void	draw_map_2D(t_scene *sc);
void	draw_player(t_scene *sc);
void	calculate_rays(t_scene *sc);
void	print_map(t_scene *sc);

//READ DATA (SETTINGS + MAP)
void	read_map(t_scene *sc, char *path);
void	read_map_for_init(t_scene *sc, char **row, int *fd);
void 	read_data_before_map(t_scene *sc, char *path, int *fd);
void	check_file_extension(t_scene *sc, char *path);
int	count_map_cols(char *r);
void	skip_empty_lines(char **row, int *fd);
void	read_config_lines(t_scene *sc, char **row, int *lines);
void	skip_config_lines(char **row, int *fd);
int	empty_line(char *row);

//TEXTURES
void	texture_cycle(t_scene *sc);
void	read_texture_file_data(t_scene *sc, char *row, int j);

//FLOOR - CEILING
void	draw_floor_ceiling(t_scene *sc);
void	get_rgb_values(t_scene *sc, char *row, int i, char type);

//CONTROLS
int	key_press(int keycode, void *param);

//PLAYER

void	move_up(t_scene *sc);
void	move_down(t_scene *sc);
void	move_left(t_scene *sc);
void	move_right(t_scene *sc);
void	rotate_left(t_scene *sc);
void	rotate_right(t_scene *sc);
void	put_player_on_map(t_scene *sc, char dir, int x, int y);

//UTILS
void	ft_bzero(void *s, size_t n);
int	no_value(char *row, int i);
int	missing_commas(char *row);
int	get_len(char *row, int i);

//FREE
void	free_doublerow_ceilfloor(t_scene *sc, char *row, char message);
void	free_doublerow_texture(t_scene *sc, char *row, char *path);
void	free_wrong_key(t_scene *sc, char *row);
void	free_missing_map(t_scene *sc, char *row);
void	free_empty_file(t_scene *sc);
void	free_invalid_map(t_scene *sc);
void	free_missing_file(t_scene *sc, char *row, char *path);
void	free_map_wrong(t_scene *sc, char *row);
void	free_map_validity_check(t_scene *sc, char message);
void	free_texture(t_scene *sc);

void	clear_buffer(t_scene *sc);
int	scene_loop(t_scene *sc);
int	close_window(void *param);


