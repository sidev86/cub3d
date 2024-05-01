#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define W_WIDTH 640
# define W_HEIGHT 480
# define T_WIDTH 64
# define T_HEIGHT 64
# define PI 3.1415926535
# define DGR 0.0174533
# define VISITED 'x'

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		olddir_x;
	double		old_plane_x;
	double		delta_x;
	double		delta_y;
	double		angle;
	double		move_speed;
	double		rot_speed;
	int			size;
}				t_player;

typedef struct s_map
{
	int			map_x;
	int			map_y;
	int			map_size;
	char		**room;
	int			rows;
	int			cols;
	int			map_present;
}				t_map;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_camera
{
	double		x;
	double		y;
	double		plane_x;
	double		plane_y;
}				t_camera;

typedef struct s_img
{
	void		*img;
	int			*data_addr;

	int			line_width;
	int			bpp;
	int			endian;
	int			img_w;
	int			img_h;
}				t_img;

typedef struct s_scene
{
	void		*mlx;
	void		*win;

	int			color;
	int			buff[W_HEIGHT][W_WIDTH];
	int			**texture;
	int			tex_x;
	int			tex_y;
	int			re_buf;
	int			init_tex;
	int			floor[3];
	int			ceil[3];
	int			f;
	int			c;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			text_init;
	int			rows;
	double		wall_x;
	double		step;
	double		tex_pos;
	char		*t_path;

	t_player	*player;
	t_map		*map;
	t_ray		*ray;
	t_camera	*cam;
	t_img		img;
}				t_scene;

void			check_map_validity(t_scene *sc);
// INIT
void			init_scene(t_scene *sc, char *path);
void			init_texture(t_scene *sc, char *row, int i);
void			init_floor_ceiling_colors(t_scene *sc, char *row, int i);
void			set_initial_ray_data(t_scene *sc, int x);

// DRAW
void			calculate_rays(t_scene *sc);
void			print_map(t_scene *sc);

// READ DATA (SETTINGS + MAP)
void			read_map(t_scene *sc, char *path);
void			read_map_for_init(t_scene *sc, char **row, int *fd);
void			check_file_extension(t_scene *sc, char *path);
void			skip_empty_lines(char **row, int *fd);
void			read_config_lines(t_scene *sc, char **row, int *lines);
void			skip_config_lines(char **row, int *fd);
int				empty_line(char *row);
void			check_row_validity(t_scene *sc, char *row);

// TEXTURES
void			texture_cycle(t_scene *sc);
void			read_texture_file_data(t_scene *sc, char *row, int j);
void			texture_to_draw(t_scene *sc, int x);

// FLOOR - CEILING
void			draw_floor_ceiling(t_scene *sc);
void			get_rgb_values(t_scene *sc, char *row, int i, char type);

// CONTROLS
int				key_press(int keycode, void *param);

// PLAYER
void			move_up(t_scene *sc);
void			move_down(t_scene *sc);
void			move_left(t_scene *sc);
void			move_right(t_scene *sc);
void			rotate_left(t_scene *sc);
void			rotate_right(t_scene *sc);
void			put_player_on_map(t_scene *sc, char dir, int x, int y);

// UTILS
int				no_value(char *row, int i);
int				missing_commas(char *row);
int				get_len(char *row, int i);
int				ft_atoi(const char *str);

// FREE
void			free_doublerow_ceilfloor(t_scene *sc, char *row, char message);
void			free_doublerow_texture(t_scene *sc, char *row, char *path, char message);
void			free_wrong_key(t_scene *sc, char *row);
void			free_missing_map(t_scene *sc, char *row);
void			free_empty_file(t_scene *sc);
void			free_invalid_map(t_scene *sc, char message);
void			free_missing_file(t_scene *sc, char *row, char *path);
void			free_map_wrong(t_scene *sc, char *row);
void			free_map_validity_check(t_scene *sc, char message);
void			free_texture(t_scene *sc);

void			clear_buffer(t_scene *sc);
int				scene_loop(t_scene *sc);
int				close_window(void *param);
#endif
