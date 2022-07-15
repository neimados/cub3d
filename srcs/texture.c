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

static void	ft_init_textures2(t_struct *game)
{
	game->tex.n = mlx_get_data_addr(game->tex.n, &game->display.bits_per_pixel,
			&game->display.line_length, &game->display.endian);
	game->tex.s = mlx_get_data_addr(game->tex.s, &game->display.bits_per_pixel,
			&game->display.line_length, &game->display.endian);
	game->tex.e = mlx_get_data_addr(game->tex.e, &game->display.bits_per_pixel,
			&game->display.line_length, &game->display.endian);
	game->tex.w = mlx_get_data_addr(game->tex.w, &game->display.bits_per_pixel,
			&game->display.line_length, &game->display.endian);
	ft_init_bonus(game);
}

void	ft_init_textures(t_struct *game)
{
	game->tex.size = TEXTURE;
	if (game->tex.n == NULL)
		game->tex.n = mlx_xpm_file_to_image(game->mlx, game->map.no,
				&game->tex.size, &game->tex.size);
	if (game->tex.s == NULL)
		game->tex.s = mlx_xpm_file_to_image(game->mlx, game->map.so,
				&game->tex.size, &game->tex.size);
	if (game->tex.e == NULL)
		game->tex.e = mlx_xpm_file_to_image(game->mlx, game->map.ea,
				&game->tex.size, &game->tex.size);
	if (game->tex.w == NULL)
		game->tex.w = mlx_xpm_file_to_image(game->mlx, game->map.we,
				&game->tex.size, &game->tex.size);
	if (!game->tex.n || !game->tex.s || !game->tex.e || !game->tex.w)
	{
		ft_free_all(game);
		write(2, "Texture failed\n", 15);
		exit(EXIT_FAILURE);
	}
	ft_init_textures2(game);
}

void	ft_ray_texture(t_struct *g)
{
	if (g->ray.side == 0 && (g->ray.mapx < g->ray.posx))
		g->tex.color = (int *)g->tex.n;
	else if (g->ray.side == 0 && (g->ray.mapx > g->ray.posx))
		g->tex.color = (int *)g->tex.s;
	else if (g->ray.side == 1 && (g->ray.mapy > g->ray.posy))
		g->tex.color = (int *)g->tex.e;
	else if (g->ray.side == 1 && (g->ray.mapy < g->ray.posy))
		g->tex.color = (int *)g->tex.w;
	if (g->ray.side == 0)
		g->tex.wall = g->ray.posy + g->ray.perpwalldist * g->ray.raydiry;
	else
		g->tex.wall = g->ray.posx + g->ray.perpwalldist * g->ray.raydirx;
	g->tex.wall -= floor((g->tex.wall));
	g->tex.x = (int)(g->tex.wall * g->tex.size);
	if (g->ray.side == 0 && g->ray.raydirx > 0)
		g->tex.x = g->tex.size - g->tex.x - 1;
	else if (g->ray.side == 1 && g->ray.raydiry < 0)
		g->tex.x = g->tex.size - g->tex.x - 1;
	g->tex.step = 1.0 * g->tex.size / g->ray.lineheight;
	g->tex.pos = (g->ray.drawstart - g->ray.ry / 2
			+ g->ray.lineheight / 2) * g->tex.step;
}
