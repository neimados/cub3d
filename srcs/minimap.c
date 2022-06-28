/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:47:10 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 12:48:34 by dso              ###   ########.fr       */
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
	game->minimap.img = NULL;
	game->minimap.addr = NULL;
	game->minimap.bits_per_pixel = 0;
	game->minimap.line_length = 0;
	game->minimap.endian = 0;
	
	//game->minimap.img = mlx_new_image(game->mlx, 200, 200);
	//game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->minimap.bits_per_pixel, &game->minimap.line_length, &game->minimap.endian);
	//my_mlx_pixel_put(&game->minimap, 5, 5, 0x00FF0000);
	//mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
}
