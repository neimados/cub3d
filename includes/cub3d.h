/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:35:41 by dso               #+#    #+#             */
/*   Updated: 2022/04/16 19:21:59 by dso              ###   ########.fr       */
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

int			ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
char		*get_next_line(int fd);
char		*ft_read(int fd, char *buffer);
char		*ft_strchr2(const char *str, int c);
char		*ft_findnl(char *buffer);
char		*ft_carry(char *buffer);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_error(char *str);

typedef struct s_map
{
	char	**map;
	char	*textures[4];
	int		sol;
	int		plafond;
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
	t_map		map;
	t_player	player;
}			t_struct;

#endif
