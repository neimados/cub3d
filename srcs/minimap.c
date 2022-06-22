/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:47:10 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/22 17:46:02 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_put_minimap(t_struct *game)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		max_i;
	int		max_j;

	i = game->player.y - 2;
	max_i = i + 6;
	while (++i <= max_i)
	{
		j = game->player.x - 6;
		max_j = j + 8;
		while (++j <= max_j)
		{
			x = MAP_WIDTH - ((max_j - j) * 16) - 16;
			y = ((max_i - i - 1) * 16);
			printf(">%d %d => %d %d\n", i, j, game->player.x, game->player.y);
			if (!game->map.map[i][j] || game->map.map[i][j] != '0')
				mlx_put_image_to_window(game->map.mlx, game->map.win,game->map.img->min_wall, x, y);
			else if (game->player.x == j && game->player.y == i)
			{
				mlx_put_image_to_window(game->map.mlx, game->map.win,game->map.img->ping, x, y);
				printf("YESSS\n");
			}
			else
				mlx_put_image_to_window(game->map.mlx, game->map.win,game->map.img->min_floor, x, y);
		}
	}
}