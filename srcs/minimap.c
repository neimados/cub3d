/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:33:58 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/29 20:48:46 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_init_minimap(t_struct *game)
{
	game->minimap.img = NULL;
	game->minimap.addr = NULL;
	game->minimap.bits_per_pixel = 0;
	game->minimap.line_length = 0;
	game->minimap.endian = 0;
	game->minimap.img = mlx_new_image(game->mlx, (game->map.width * 10),
			(game->map.height * 10));
	game->minimap.addr = (int *)mlx_get_data_addr(
			game->minimap.img,
			&game->minimap.bits_per_pixel,
			&game->minimap.line_length,
			&game->minimap.endian);
}

static void	ft_minimap_back(t_struct *game, int x, int y)
{
	while (x < game->map.width * 10)
	{
		while (y < game->map.height * 10)
		{
			game->minimap.addr[y * (game->map.width * 10) + x] = 0xA1A7B8;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	while (x < game->map.width * 10)
	{
		while (y < game->map.height * 10)
		{
			if (y > 0 && y / 10 < game->map.height)
				if (x > 0 && x / 10 < ft_strlen(game->map.map[y / 10]))
					if (game->map.map[y / 10][x / 10] == '0')
						game->minimap.addr[y * (game->map.width
								* 10) + x] = 0x00FFFFFF;
			y++;
		}
		y = 0;
		x++;
	}
}

void	ft_put_minimap(t_struct *game)
{
	int	x;
	int	y;

	ft_init_minimap(game);
	ft_minimap_back(game, 0, 0);
	y = -2;
	x = -2;
	while (x < 4)
	{
		while (y < 4)
		{
			game->minimap.addr[(int)(game->map.pos_x * 10 + x)
				*(game->map.width * 10)
				+ (int)(game->map.pos_y * 10 + y)] = 0x00FF0000;
			y++;
		}
		y = -2;
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img,
		(MAP_WIDTH - (game->map.width * 10)), 0);
	mlx_destroy_image(game->mlx, game->minimap.img);
}
