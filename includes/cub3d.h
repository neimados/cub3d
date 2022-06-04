/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:35:41 by dso               #+#    #+#             */
/*   Updated: 2022/06/04 11:52:43 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	long	f;
	long	c;
}			t_map;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}			t_player;

typedef struct s_struct
{
	void		*mlx;
	void		*win;
	int			count;
	int			pos;
	char		*maptmp;
	t_map		map;
	t_player	player;
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

#endif
