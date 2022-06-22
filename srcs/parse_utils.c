/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/06/22 14:45:38 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_pos(t_struct *game)
{
	int	i;
	int	j;

	i = 0;
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
	if (game->player.direction == 'N')
		game->player.dir_y = -1;
	if (game->player.direction == 'S')
		game->player.dir_y = 1;
	if (game->player.direction == 'E')
		game->player.dir_x = -1;
	if (game->player.direction == 'W')
		game->player.dir_x = -1;
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
