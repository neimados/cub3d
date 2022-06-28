/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:33:58 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 15:56:05 by dvergobb         ###   ########.fr       */
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
	game->minimap = malloc(sizeof(t_data));
	game->minimap->img = NULL;
	game->minimap->addr = NULL;
	game->minimap->bits_per_pixel = 0;
	game->minimap->line_length = 0;
	game->minimap->endian = 0;
	game->minimap->img = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
	game->minimap->addr = mlx_get_data_addr(
		game->minimap->img,
		&game->minimap->bits_per_pixel,
		&game->minimap->line_length,
		&game->minimap->endian);
	int i = -1;
	int j = -1;
	while (++i < MINIMAP_W)
	{
		// printf(">> %d\n", MINIMAP_W);
		while (++j < MINIMAP_H)
			my_mlx_pixel_put(game->minimap, i, j, 0x00FF0000);
		j = -1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap->img, (MAP_WIDTH - 120), 0);
}
