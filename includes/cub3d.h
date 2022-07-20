/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:46:49 by dvergobb          #+#    #+#             */
/*   Updated: 2022/07/20 09:03:43 by dvergobb         ###   ########.fr       */
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
# define TOUCHM 46
# define TOUCHX 7
# define TEXTURE 64

# define MAP_WIDTH 800
# define MAP_HEIGHT 600

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

typedef struct s_ray {
	int		rx;
	int		ry;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
	double	raydirx;
	double	raydiry;
	double	camerax;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	float	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		x;
	float	speed;
	float	tspeed;
}				t_ray;

typedef struct s_data {
	void	*img;
	int		*addr;
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

typedef struct s_texture
{
	void		*n;
	void		*s;
	void		*e;
	void		*w;
	int			size;
	float		wall;
	int			*color;
	int			x;
	int			y;
	float		step;
	float		pos;
}			t_texture;

typedef struct s_struct
{
	int			time;
	int			bonusx;
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
	int			minim;
	int			bonus;
	void		*bonust[10];
	t_map		map;
	t_data		minimap;
	t_data		display;
	t_player	player;
	t_ray		ray;
	t_texture	tex;
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
void		ft_error(char *str);
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
void		ft_init_display(t_struct *game);
void		ft_init_ray(t_struct *game);
void		ft_init_textures(t_struct *game);
void		ft_init_bonus(t_struct *game);
void		ft_free_all(t_struct *game);
void		ft_ray_texture(t_struct *game);
void		ft_ray_draw_bonus(t_struct *game);
void		ft_ray_texture_bonus(t_struct *game);
void		ft_ray_step(t_struct *game);
int			ft_get_keys(t_struct *game);
int			ft_key_release(int keycode, t_struct *game);
int			ft_key_press(int keycode, t_struct *game);
void		ft_exit_prog(t_struct *game, char *str);
int			ft_abort_prog(t_struct *game);
void		ft_put_minimap(t_struct *game);
void		ft_left_right(t_struct *game);
void		ft_move(t_struct *game);
void		ft_rotate_right(t_struct *game);
void		ft_rotate_left(t_struct *game);

#endif
