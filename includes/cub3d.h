/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:46:49 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/29 20:46:02 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 1
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESCAPE 53
# define TURN_RIGHT 124
# define TURN_LEFT 123

# define MAP_WIDTH 1000
# define MAP_HEIGHT 800

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

typedef struct	s_ray {
	int		rx; //width de la fenetre
	int		ry; //height de la fenetre
	double	posx; //position x du joueur
	double	posy; //position y du joueur
	double	dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double	diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double	planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double	plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double	raydirx; //calcul de direction x du rayon
	double	raydiry; //calcul de direction y du rayon
	double	camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos
	double	sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double	sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double	deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double	deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int		stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int		stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int		hit; // 1 si un mur a ete touche, 0 sinon
	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double	perpwalldist; // distance du joueur au mur
	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner
	int		x; //permet de parcourir tous les rayons
	double	speed;//vitesse pour avancer
	double	tspeed;//vitesse pour tourner
}				t_ray;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	long	f;
	long	c;
	int		height;
	int		width;
	double	pos_x;
	double	pos_y;
}			t_map;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}			t_player;

typedef struct s_struct
{
	int			time;
	int			key_up;
	int			key_down;
	int			key_right;
	int			key_left;
	int			key_turn_left;
	int			key_turn_right;
	void		*mlx;
	void		*win;
	int			count;
	int			pos;
	char		*maptmp;
	t_map		map;
	t_data		*minimap;
	t_data		display;
	t_player	player;
	t_ray		ray;
}			t_struct;

int			ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
char		*get_next_line(int fd);
char		*ft_strchr2(const char *str, int c);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_strcmp(char *a, char *b);
int			ft_isdigit(int c);
int			ft_iswhitesp(char c);
char		**ft_split(char *s, char *c);
char		*ft_strchr(const char *str, int c);
int			counttab(char **tab);
char		*ft_strdup(const char *str);
int			ft_atoi(const char *str);
int			ft_check_digit(char **tmp2);
int			ft_error(char *str);
void		ft_free_tmp(char **tmp);
int			ft_free_parse(t_struct *game, char **tmp);
char		*ft_strjoin(char *s1, char *s2);
int			ft_check_map_ext(char *filename);
int			ft_check_conf(t_struct *game);
int			ft_check_duplicate(t_struct *game, char **tmp);
int			ft_check_map(t_struct *game);
int			ft_check_color(char *tmp);
t_struct	ft_init_struct(void);
void		player_pos(t_struct *game, int i, int j);
int			ft_gnl(char *av, t_struct *game);
int			ft_error_gnl(char *str);
long		ft_color_calc(char **tmp);
int			ft_parse(char *str, t_struct *game);
int			ft_free_struct(t_struct *game);
int			ft_map_height(char **map);
int			ft_map_width(char **map);
void		ft_display(t_struct *game);

int			ft_get_keys(t_struct *game);
int			ft_key_release(int keycode, t_struct *game);
int			ft_key_press(int keycode, t_struct *game);
void		ft_exit_prog(t_struct *game, char *str);
int			ft_abort_prog(t_struct *game);
void		ft_put_minimap(t_struct *game);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
