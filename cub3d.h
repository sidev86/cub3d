#include <stdlib.h>

#define W_WIDTH 800
#define W_HEIGHT 600

typedef struct s_player
{
	int posX;
	int posY;
	int size;
}	t_player;

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
}	t_scene;



