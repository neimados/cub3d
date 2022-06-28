/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:14:47 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 10:15:13 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	ft_free_tmp(char **tmp)
{
	int	i;

	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

int	ft_free_parse(t_struct *game, char **tmp)
{
	int	i;

	i = -1;
	ft_free_tmp(tmp);
	if (game->map.no)
		free(game->map.no);
	if (game->map.so)
		free(game->map.so);
	if (game->map.we)
		free(game->map.we);
	if (game->map.ea)
		free(game->map.ea);
	if (game->map.map)
	{
		while (game->map.map[++i])
			free(game->map.map[i]);
	}
	if (game->maptmp)
		free(game->maptmp);
	return (1);
}

int	ft_free_struct(t_struct *game)
{
	int	i;

	i = -1;
	if (game->map.no)
		free(game->map.no);
	if (game->map.so)
		free(game->map.so);
	if (game->map.we)
		free(game->map.we);
	if (game->map.ea)
		free(game->map.ea);
	if (game->map.map)
	{
		while (game->map.map[++i])
			free(game->map.map[i]);
	}
	free(game->map.map);
	return (1);
}

int	ft_error_gnl(char *str)
{
	free(str);
	return (1);
}
