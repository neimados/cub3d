/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 10:11:37 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_display(t_struct *game)
{
	game->display.img = NULL;
	game->display.addr = NULL;
	game->display.bits_per_pixel = 0;
	game->display.line_length = 0;
	game->display.endian = 0;
	game->display.img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	game->display.addr = mlx_get_data_addr(
		game->display.img,
		&game->display.bits_per_pixel,
		&game->display.line_length,
		&game->display.endian);
}

void	ft_display(t_struct *game)
{
	ft_init_display(game);
	game->rc.rayon = 0;
	while (game->rc.rayon < MAP_WIDTH)
	{
		//PRINT PIXELS PAR COLONNES
		game->rc.rayon += 1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
}