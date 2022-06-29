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

// static void ft_rectangle()
// {
	
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_put_minimap(t_struct *game)
{
	float	minimap_size;
	
	printf("> Coucou, map reload\n");
	minimap_size = MAP_WIDTH * 0.18;
	if (MAP_HEIGHT > MAP_WIDTH)
		minimap_size = MAP_HEIGHT * 0.18;
	game->minimap = malloc(sizeof(t_data));
	game->minimap->img = NULL;
	game->minimap->addr = NULL;
	game->minimap->bits_per_pixel = 0;
	game->minimap->line_length = 0;
	game->minimap->endian = 0;
	game->minimap->img = mlx_new_image(game->mlx, minimap_size, minimap_size);
	game->minimap->addr = mlx_get_data_addr(
		game->minimap->img,
		&game->minimap->bits_per_pixel,
		&game->minimap->line_length,
		&game->minimap->endian);
	int i = -1;
	int j = -1;
	while (++i < minimap_size)
	{
		while (++j < minimap_size)
			my_mlx_pixel_put(game->minimap, i, j, 0x00FF0000);
		j = -1;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->minimap->img, (MAP_WIDTH - minimap_size), 0);
}
