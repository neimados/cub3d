/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:14:47 by dso               #+#    #+#             */
/*   Updated: 2022/06/18 11:15:12 by dso              ###   ########.fr       */
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
	if (tmp)
	{
		while (tmp[++i])
			free(tmp[i]);
		free(tmp);
	}
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
		i = -1;
		while (game->map.map[++i])
			free(game->map.map[i]);
	}
	if (game->maptmp)
		free(game->maptmp);
	return (1);
}
