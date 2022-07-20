/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/07/20 11:38:53 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_pos(t_struct *game, int i, int j)
{
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
			|| game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.x = j;
				game->player.y = i;
				game->player.direction = game->map.map[i][j];
				game->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (game->player.x == 0 || game->player.y == 0)
		ft_error("Error\nNo player's position\n");
}

int	ft_gnl(char *av, t_struct *game)
{
	int		fd;
	char	*str;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (1);
	str = get_next_line(fd);
	if (!str)
		return (1);
	while (str)
	{
		if (ft_parse(str, game) == 1)
		{
			free(str);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
	}
	game->map.map = ft_split(game->maptmp, "\n");
	free(game->maptmp);
	if (!game->map.map)
		return (1);
	return (0);
}

static char	**ft_color_calc_split(char **tmp)
{
	char	*tmp3;
	char	**tmp2;
	int		i;

	i = 1;
	tmp3 = ft_calloc(1, sizeof(char));
	while (tmp[i])
	{
		tmp3 = ft_strjoin2(tmp3, tmp[i]);
		i++;
	}
	if (ft_check_color(tmp3) == 1)
	{
		free(tmp3);
		return (NULL);
	}
	tmp2 = ft_split(tmp3, " \t\n\v\f\r,");
	free(tmp3);
	return (tmp2);
}

long	ft_color_calc(char **tmp)
{
	char	**tmp2;
	int		r;
	int		g;
	int		b;

	tmp2 = ft_color_calc_split(tmp);
	if (!tmp2 || counttab(tmp2) != 3)
	{
		ft_free_tmp(tmp2);
		return (-1);
	}
	if (ft_check_digit(tmp2) == 1)
	{
		ft_free_tmp(tmp2);
		return (-1);
	}
	r = ft_atoi(tmp2[0]);
	g = ft_atoi(tmp2[1]);
	b = ft_atoi(tmp2[2]);
	ft_free_tmp(tmp2);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	return ((r * 256 * 256) + (g * 256) + b);
}

int	ft_error_gnl(char *str)
{
	free(str);
	return (1);
}
