#include "cub3d.h"

static int	*calculate_sign(int p1x, int p1y, int p2x, int p2y)
{
	int	*sign;
	
	sign = malloc(sizeof(int) * 2);
	if (p1x < p2x)
		sign[0] = 1;
	else
		sign[0] = -1;
	if (p1y < p2y)
		sign[1] = 1;
	else
		sign[1] = -1;
	return (sign);
}

static int	*absolute_delta(int p1x, int p1y, int p2x, int p2y)
{
	int	*delta;

	delta = malloc(sizeof(int) * 2);
	delta[0] = abs(p2x - p1x);
	delta[1] = abs(p2y - p1y);
	return (delta);
}

/*static float dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}*/


void	draw_rays_3D(t_scene *sc)
{
	int x;
	int p1[2];
	int p2[2];

	// Ciclo per ogni colonna della schermata
	for (x = 0; x < W_WIDTH; x++)
	{
	// Calcolo la posizione della colonna sulla telecamera
	sc->cam->x = 2 * x / (float)W_WIDTH - 1;

	// Direzione del raggio dal giocatore alla colonna della schermata
	sc->ray->dirX = sc->player->dirX + sc->cam->planeX * sc->cam->x;
	sc->ray->dirY = sc->player->dirY + sc->cam->planeY * sc->cam->x;

	// Posizione della mappa del giocatore
	sc->map->mapX = (int)sc->player->posX;
	sc->map->mapY = (int)sc->player->posY;

	

	// Lunghezza del raggio dall'attuale posizione alla prossima linea x o y della griglia, considerando solo una unità di griglia
	sc->ray->deltaDistX = fabs(1 / sc->ray->dirX);
	sc->ray->deltaDistY = fabs(1 / sc->ray->dirY);

	

	sc->ray->hit = 0; // Flag per indicare se il raggio ha colpito un muro

	// Calcolo del passo della mappa e della distanza al primo muro in x e y
	if (sc->ray->dirX < 0)
	{
	    sc->ray->stepX = -1;
	    sc->ray->sideDistX = (sc->player->posX - sc->map->mapX) * sc->ray->deltaDistX;
	}
	else
	{
	    sc->ray->stepX = 1;
	    sc->ray->sideDistX = (sc->map->mapX + 1.0f - sc->player->posX) * sc->ray->deltaDistX;
	}
	if (sc->ray->dirY < 0)
	{
	    sc->ray->stepY = -1;
	    sc->ray->sideDistY = (sc->player->posY - sc->map->mapY) * sc->ray->deltaDistY;
	}
	else
	{
	    sc->ray->stepY = 1;
	    sc->ray->sideDistY = (sc->map->mapY + 1.0 - sc->player->posY) * sc->ray->deltaDistY;
	}

	// Algoritmo DDA
	while (!sc->ray->hit)
	{
	    // Sposta il raggio alla prossima cella x o y
	    if (sc->ray->sideDistX < sc->ray->sideDistY)
	    {
		sc->ray->sideDistX += sc->ray->deltaDistX;
		sc->map->mapX += sc->ray->stepX;
		sc->ray->side = 0; // L'intersezione è orizzontale
	    }
	    else
	    {
		sc->ray->sideDistY += sc->ray->deltaDistY;
		sc->map->mapY += sc->ray->stepY;
		sc->ray->side = 1; // L'intersezione è verticale
	    }
	    
	    // Controlla se il raggio ha colpito un muro
	    if (sc->map->room[sc->map->mapX][sc->map->mapY] > 0)
		sc->ray->hit = 1;
	}

	// Calcola la distanza perpendicolare dal giocatore al muro, in base alla direzione del raggio e al tipo di intersezione
	if (sc->ray->side == 0)
	    sc->ray->perpWallDist = (sc->map->mapX - sc->player->posX + (1 - sc->ray->stepX) / 2) / sc->ray->dirX;
	else
	    sc->ray->perpWallDist = (sc->map->mapY - sc->player->posY + (1 - sc->ray->stepY) / 2) / sc->ray->dirY;

	// Calcola l'altezza della linea da disegnare sulla schermata
	sc->ray->lineHeight = (int)(W_HEIGHT / sc->ray->perpWallDist);

	// Calcola le coordinate di inizio e fine della linea da disegnare
	sc->ray->drawStart = -sc->ray->lineHeight / 2 + W_HEIGHT / 2;
	if (sc->ray->drawStart < 0)
	    sc->ray->drawStart = 0;
	sc->ray->drawEnd = sc->ray->lineHeight / 2 + W_HEIGHT / 2;
	if (sc->ray->drawEnd >= W_HEIGHT)
	    sc->ray->drawEnd = W_HEIGHT - 1;
	
	p1[0] = x;
	p1[1] = sc->ray->drawStart;
	p2[0] = x;
	p2[1] = sc->ray->drawEnd;
	// Disegna la linea sulla schermata
	sc->color = (sc->ray->side == 0) ? 0x00FF00 : 0x008800; // Colore della linea
	draw_line(sc, p1, p2);
	}

}

void	draw_line(t_scene *sc, int *p1, int *p2)
{
	int *delta;
	int *sign;
	int cur[2];
	int		e1;
	int		e2;

	delta = absolute_delta(p1[0], p1[1], p2[0], p2[1]);
	sign = calculate_sign(p1[0], p1[1], p2[0], p2[1]);
	e1 = delta[0] - delta[1];
	cur[0] = p1[0];
	cur[1] = p1[1]; 
	while (cur[0] != p2[0] || cur[1] != p2[1])
	{
		put_pixel(sc, cur[0], cur[1], sc->color);
		e2 = e1 * 2;
		if (e2 > -delta[1])
		{
			e1 -= delta[1];
			cur[0] += sign[0];
		}
		if (e2 < delta[0])
		{
			e1 += delta[0];
			cur[1] += sign[1];
		}
	}
}
