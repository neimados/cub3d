/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/06/18 16:25:52 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_textures(t_struct *game)
{
	game->texturesize = TEXTURE;
	game->texturen =  mlx_xpm_file_to_image(game->mlx, game->map.no, &game->texturesize, &game->texturesize);
	game->textures =  mlx_xpm_file_to_image(game->mlx, game->map.so, &game->texturesize, &game->texturesize);
	game->texturee =  mlx_xpm_file_to_image(game->mlx, game->map.ea, &game->texturesize, &game->texturesize);
	game->texturew =  mlx_xpm_file_to_image(game->mlx, game->map.we, &game->texturesize, &game->texturesize);
	if (!game->texturen || !game->textures || !game->texturee || !game->texturew)
	{
		ft_free_all(game);
		write(2, "Texture failed\n", 15);
		exit(EXIT_FAILURE);
	}
	game->texturen = mlx_get_data_addr(game->texturen, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->textures = mlx_get_data_addr(game->textures, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->texturee = mlx_get_data_addr(game->texturee, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->texturew = mlx_get_data_addr(game->texturew, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
}

// void	ft_ray_texture(t_struct *game)
// {

// }
