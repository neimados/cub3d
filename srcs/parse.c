/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 13:14:35 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_fillconf_fc(t_struct *game, char **tmp)
{
	if (!ft_strcmp(tmp[0], "F"))
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
	return (0);
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
	else if (!ft_strcmp(tmp[0], "F") || (!ft_strcmp(tmp[0], "C")))
		if (ft_fillconf_fc(game, tmp) == 1)
			return (1);
	ft_free_tmp(tmp);
	return (0);
}

int	ft_parse_conf(t_struct *game, char **tmp, char *str)
{
	int	i;

	i = 0;
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
	return (0);
}

int	ft_parse_map(t_struct *game, char **tmp, char *str)
{
	int	i;

	i = 0;
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
	return (0);
}

int	ft_parse(char *str, t_struct *game)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (game->count != 6)
		return (ft_parse_conf(game, tmp, str));
	else
		return (ft_parse_map(game, tmp, str));
	return (0);
}
