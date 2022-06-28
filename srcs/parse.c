/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 12:44:53 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long	ft_color_calc(char **tmp)
{
	char	*tmp3;
	char	**tmp2;
	int	r;
	int	g;
	int	b;
	int	i;

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
		return (-1);
	}
	tmp2 = ft_split(tmp3, " \t\n\v\f\r,");
	free(tmp3);
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

int	ft_fillconf(t_struct *game, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO") || !ft_strcmp(tmp[0], "SO")
	|| !ft_strcmp(tmp[0], "WE") || !ft_strcmp(tmp[0], "EA"))
	{
		if (counttab(tmp) != 2)
			return (1);
		if (ft_check_duplicate(game, tmp) == 1)
			return (1);
	}
	else if (!ft_strcmp(tmp[0], "F"))
	{
		if (game->map.f != -1)
			return (1);
		game->map.f = ft_color_calc(tmp);
		if (game->map.f == -1)
			return (1);
	}
	else if (!ft_strcmp(tmp[0], "C"))
	{
		if (game->map.c != -1)
			return (1);
		game->map.c = ft_color_calc(tmp);
		if (game->map.c == -1)
			return (1);
	}
	ft_free_tmp(tmp);
	return (0);
}

int	ft_parse(char *str, t_struct *game)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (game->count != 6)
	{
		while (str[i] && (ft_iswhitesp(str[i]) == 1 || str[i] == ' '))
			i++;
		if (str[i])
		{
			game->count += 1;
			tmp = ft_split(str, " \t\n\v\f\r");
			if (!tmp)
				return (ft_free_parse(game, tmp));
			if (ft_fillconf(game, tmp) == 1)
				return (ft_free_parse(game, tmp));
			return (0);
		}
	}
	else
	{
		while (str[i])
		{
			if (game->pos != 0)
				if (ft_iswhitesp(str[0]) == 1)
					str[0] = 'x';
			if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
				game->pos = 1;
			i++;
		}
		if (game->pos != 0)
		{
			game->maptmp = ft_strjoin(game->maptmp, str);
			if (!game->maptmp)
				return (ft_free_parse(game, tmp));
			return (0);
		}
	}
	return (0);
}
