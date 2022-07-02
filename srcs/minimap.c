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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_put_minimap(t_struct *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->minimap = malloc(sizeof(t_data));
	game->minimap->img = NULL;
	game->minimap->addr = NULL;
	game->minimap->bits_per_pixel = 0;
	game->minimap->line_length = 0;
	game->minimap->endian = 0;
	game->minimap->img = mlx_new_image(game->mlx, (game->map.width * 10), (game->map.height * 10));
	game->minimap->addr = mlx_get_data_addr(
		game->minimap->img,
		&game->minimap->bits_per_pixel,
		&game->minimap->line_length,
		&game->minimap->endian);
	while (y < game->map.height * 10)//BACKGROUND
	{
		while (x < game->map.width * 10)
		{
			my_mlx_pixel_put(game->minimap, x, y, 0xA1A7B8);
			x++;
		}
		x = 0;
		y++;
	}
	y = 0;
	while (y < game->map.height * 10)//MINIMAP
	{
		while (x < game->map.width * 10)
		{
			if (y > 0 && y / 10 < game->map.height)
				if (x > 0 && x / 10 < ft_strlen(game->map.map[y / 10]))
					if (game->map.map[y / 10][x / 10] == '0')
						my_mlx_pixel_put(game->minimap, x, y, 0x00FFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	y = -2;
	x = -2;
	while (y < 4)//PLAYER
	{
		while (x < 4)
		{
			my_mlx_pixel_put(game->minimap, game->map.pos_x  * 10 + x, game->map.pos_y * 10 + y, 0x00FF0000);
			x++;
		}
		x = -2;
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap->img, (MAP_WIDTH - (game->map.width * 10)), 0);
}
