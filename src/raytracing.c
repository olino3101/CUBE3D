#include "cub3d.h"

void	cal_sidedist(t_rc *rc, t_data *data)
{
	rc->mapx = (int)data->px;
	rc->mapy = (int)data->py;
	// step est dans quel axe que ca va dans map
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (data->px - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1 - data->px) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (data->py - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1 - data->py) * rc->deltadisty;
	}
}

void	dda_process(t_rc *rc, t_data *data)
{
	// jump toujours de une case de map a la fois
		// just attend que ca hit
	while (!rc->hit)
	{
		if (rc->sidedistx < rc->sidedisty) // change de case dans le x
		{
			rc->sidedistx += rc->deltadistx;
			rc->mapx += rc->stepx;
			rc->side = 0; // la direction
		}
		else // change de case dans le y
		{
			rc->sidedisty += rc->deltadisty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (data->map[rc->mapx][rc->mapy] > 0)
			rc->hit = true; // mur trouver
	}
	rc->hit = false;
}

void	prints_screen(t_print_tex texs, t_data *data)
{
	int	starty;
	int	endy;

	starty = -texs.lineheight / 2 + H / 2;
	if (starty < 0)
		starty = 0;
	endy = texs.lineheight / 2 + H / 2;
	if (endy >= H)
		endy = H - 1;
	verline(texs, starty, endy, data);
}

static	void	rt_calculate(t_rc *rc, int x, t_data *data)
{
	// map pour etre tjrs en 1 et -1 0 representant le centre
	rc->camerax = 2 * x / (double)W - 1;

	// calcul la direction du ray
	rc->raydirx = data->dirx + data->planex * rc->camerax;
	rc->raydiry = data->diry + data->planey * rc->camerax;
	
	// ie30 ca veut dire une rtes grosse value genre le plu proche de linfini typeshit
	// si par exemple raydirx == 0 ca veut dire que ca va jamais changer de case vers les x donc toujours rester dans le deltadisty
	if (rc->raydirx == 0)
		rc->deltadistx = 1e30;
	else
		rc->deltadistx = fabs(1 / rc->raydirx);
	if (rc->raydiry == 0)
		rc->deltadisty = 1e30;
	else
		rc->deltadisty = fabs(1 / rc->raydiry);
	cal_sidedist(rc, data);
	dda_process(rc, data);

	// dependamment si le coter hit est x ou y on calcule sois avec un sois lautre
	// calcul la distance projeter sur la camera direction
	if (rc->side == 0)
		rc->perpwalldist = rc->sidedistx - rc->deltadistx;
	else
		rc->perpwalldist = rc->sidedisty - rc->deltadisty;
}

// le debut du raytracing

// le concept general cest denvoyer plein de rayon lazer pour detecter si ya un mur, apres on connais la distance,
	// selon a quel point il est loin on va print les pixels plus ou moins haut et bas sur lecran
	// jai utiliser lalgo dda pour calculer si ya un mur
void	rt(t_data *data)
{
	int		x;
	t_rc	*rc;

	rc = malloc(sizeof(t_rc));
	x = 0;
	// loop chaque x de lecran car seulement le x doit etre calculer 
	while (x != W)
	{
		// le juice des calculation
		rt_calculate(rc, x, data);
		// va calculer les calcul de print et printer chaque pixel
		prints_screen(init_print_tex(rc, x, data), data);
		//reset pour chaque loop
		rc->sidedistx = 0;
		rc->sidedisty = 0;
		x++;
	}
	free(rc);
}
