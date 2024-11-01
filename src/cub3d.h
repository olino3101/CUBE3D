#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>

# define HTEXT
# define WTEXT
# define W 1048
# define H 1048
# define WMAP 12
# define HMAP 12

# define A "./img/a.png"
// dirx 0 diry 1, planx 0.66 plany 0
# define EA "./img/brick.png"
// dirx 0 diry -1, planx -0.66 plany 0
# define WE "./img/wood.png"
# define NO "./img/plank.png"
// dirx 1 diry 0, planx 0 plany -0.66
# define SO "./img/rock.png"
// math var of the cub3d project

typedef struct s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	color;
}	t_color;

typedef struct s_print_tex
{
	int		tex_i;
	int		side;
	int		x;
	int		texx;
	int		lineheight;
	double	perpwalldist;
}	t_print_tex;

typedef struct s_data
{

	// pos du joueur toujours entre 0 et le nombre HMAP et WMAP
		//mais en double parce que il ne se deplace pas par une case chaque fois
	double			px;
	double			py;

	// la direction que le joueur regarde
		// ou ya les define tu peux voir chaque settings pour la direction quand tu lance le programme nord, sud, ouest, est
		// jsp c quoi le plus efficace pour le faire mais sinon ya aussi la formule pour tourner voir input les touches a et d
	double			dirx;
	double			diry;

	// la camera plane du joueur un peu comme le champ de vision
		// ca doit tjrs etre perpendiculaire a la direction
		// ca determine le FOV du joueur aussi
	double			planex;
	double			planey;

	// duh je pense tu sais c quoi katchow!
	float			speed;

	//la mlx
	mlx_t			*mlx;
	mlx_image_t		*img;
	// les 4 texture voir init
	mlx_texture_t	*texture[4];
	// la map en deux d
	int				**map;
}	t_data;

typedef struct s_rc
{
	// utiliser pour mapper chaque pixel entre -1 et 1 0 etant le centre
	double	camerax;
	// la direction du rayon
	double	raydirx;
	double	raydiry;

	// la position du rayon dans la map (genre yer rendu ou a la recherche dun wall)
	int		mapx;
	int		mapy;

	// calcul al distance jusquau prochain "saut de case de  la map " y faudrait que je texplique visuellement si tu captes pas
	double	deltadistx;
	double	deltadisty;

	// va etre utiliser pour calculer la longueur du ray
	double	perpwalldist;

	// la distance jusqua la prochaine ligne x ou y (souvent incrementer pour toujours trouver la prochaine ligne)
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	int		side;
	bool	hit;
}	t_rc;

t_print_tex	init_print_tex(t_rc *rc, int x, t_data *data);
void		input(void *param);
void		verline(t_print_tex texs, int y1, int y2, t_data *data);
void		rt(t_data *data);
t_data		*init(void);
void		free_ev(t_data *data);

#endif