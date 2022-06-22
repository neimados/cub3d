/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/06/18 17:00:03 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_map_ext(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 5)
		return (1);
	if (filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		return (1);
	return (0);
}

int	ft_check_conf(t_struct *game)
{
	if (game->map.f == -1 || game->map.c == -1)
		return (1);
	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea)
		return (1);
	return (0);
}

int	ft_check_duplicate(t_struct *game, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO"))
	{
		if (game->map.no)
			return (1);
		game->map.no = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "SO"))
	{
		if (game->map.so)
			return (1);
		game->map.so = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "WE"))
	{
		if (game->map.we)
			return (1);
		game->map.we = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "EA"))
	{
		if (game->map.ea)
			return (1);
		game->map.ea = ft_strdup(tmp[1]);
	}
	return (0);
}

int	ft_check_map_wall(t_struct *game, int i, int j)
{
	if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
	|| game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
	{
		if (game->pos != 0)
			game->map.map[i][j] = '0';
		else
			game->pos = 1;
	}
	if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
	|| game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E'
	|| game->map.map[i][j] == '0')
	{
		if (i == counttab(game->map.map) - 1 || i == 0)
			return (1);
		if (!game->map.map[i - 1][j] || !game->map.map[i + 1][j]
		|| !game->map.map[i][j - 1] || !game->map.map[i][j + 1])
			return (1);
		if (game->map.map[i - 1][j] == ' ' || game->map.map[i + 1][j] == ' '
		|| game->map.map[i][j - 1] == ' ' || game->map.map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

int	ft_check_map(t_struct *game)
{
	int	i;
	int	j;

	i = 0;
	game->pos = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == ' ' || game->map.map[i][j] == '0'
			|| game->map.map[i][j] == '1' || game->map.map[i][j] == 'N'
			|| game->map.map[i][j] == 'S' || game->map.map[i][j] == 'W'
			|| game->map.map[i][j] == 'E')
			{
				if (ft_check_map_wall(game, i, j) == 1)
					return (1);
			}
			else
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
