#include "cub3d.h"

static	void	walli_init(t_rc *rc, t_data *data, t_print_tex *texs)
{
	// check quel est le coter pour quel texture prendre
	if (rc->side == 1)
	{
		if (rc->mapy > data->py)
			texs->tex_i = 0;
		else
			texs->tex_i = 1;
	}
	else
	{
		if (rc->mapx > data->px)
			texs->tex_i = 2;
		else
			texs->tex_i = 3;
	}
}

t_print_tex	init_print_tex(t_rc *rc, int x, t_data *data)
{
	t_print_tex	texs;
	double		wallx;

	walli_init(rc, data, &texs);
	// wallx sert a savoir quelle parti du murs ca la ete toucher
	if (rc->side == 0)
		wallx = data->py + rc->perpwalldist * rc->raydiry;
	else
		wallx = data->px + rc->perpwalldist * rc->raydirx;
	wallx -= floor(wallx);
	// le x de la texture
	texs.texx = (int)(wallx * (double)data->texture[texs.tex_i]->width);
	texs.perpwalldist = rc->perpwalldist;
	texs.lineheight = (int)(H / texs.perpwalldist);
	texs.side = rc->side;
	texs.x = x;
	return (texs);
}

static	void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(W, H, "42balls", false);
	if (!data->mlx)
	{
		free(data->mlx);
		exit(0);
	}
	data->img = mlx_new_image(data->mlx, W, H);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		free(data);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
	{
		mlx_close_window(data->mlx);
		free(data);
		exit(0);
	}
}

static	void	init_text(t_data *data)
{
	data->texture[0] = mlx_load_png(EA);
	data->texture[1] = mlx_load_png(WE);
	data->texture[2] = mlx_load_png(SO);
	data->texture[3] = mlx_load_png(NO);
	if (!data->texture[0] || !data->texture[1] \
		|| !data->texture[2] || !data->texture[3])
	{
		fflush(stdout);
		printf("not a good texture");
		free(data);
		exit(1);
	}
}

t_data	*init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(0);
	data->px = 5.0;
	data->py = 6.45;
	data->dirx = -1.0;
	data->diry = 0.0;
	data->planex = 0;
	data->planey = 0.66;
	data->speed = 0.2;
	init_mlx(data);
	init_text(data);
	data->map = malloc(sizeof(int *) * HMAP);
	for (int i = 0; i < HMAP; i++)
		data->map[i] = malloc(sizeof(int) * WMAP);
int map[HMAP][WMAP] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 4, 0, 4, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

	for (int i = 0; i < HMAP; i++)
	{
		for( int j = 0; j < WMAP; j++)
			data->map[i][j] = map[i][j];
	}
	return (data);
}