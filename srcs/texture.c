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
	int	i;

	i = 0;
	game->tex.size = TEXTURE;
	if (game->tex.n == NULL)
		game->tex.n =  mlx_xpm_file_to_image(game->mlx, game->map.no, &game->tex.size, &game->tex.size);
	if (game->tex.s == NULL)
		game->tex.s =  mlx_xpm_file_to_image(game->mlx, game->map.so, &game->tex.size, &game->tex.size);
	if (game->tex.e == NULL)
		game->tex.e =  mlx_xpm_file_to_image(game->mlx, game->map.ea, &game->tex.size, &game->tex.size);
	if (game->tex.w == NULL)
		game->tex.w =  mlx_xpm_file_to_image(game->mlx, game->map.we, &game->tex.size, &game->tex.size);
	if (game->bonust[0] == NULL)
		game->bonust[0] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus1.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[1] == NULL)
		game->bonust[1] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus2.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[2] == NULL)
		game->bonust[2] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus3.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[3] == NULL)
		game->bonust[3] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus4.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[4] == NULL)
		game->bonust[4] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus5.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[5] == NULL)
		game->bonust[5] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus6.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[6] == NULL)
		game->bonust[6] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus7.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[7] == NULL)
		game->bonust[7] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus8.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[8] == NULL)
		game->bonust[8] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus9.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[9] == NULL)
		game->bonust[9] =  mlx_xpm_file_to_image(game->mlx, "./sprites/bonus10.xpm", &game->tex.size, &game->tex.size);
	if (!game->tex.n || !game->tex.s || !game->tex.e || !game->tex.w)
	{
		ft_free_all(game);
		write(2, "Texture failed\n", 15);
		exit(EXIT_FAILURE);
	}
	game->tex.n = mlx_get_data_addr(game->tex.n, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->tex.s = mlx_get_data_addr(game->tex.s, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->tex.e = mlx_get_data_addr(game->tex.e, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	game->tex.w = mlx_get_data_addr(game->tex.w, &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
	i = 0;
	while (i < 4)
	{
		game->bonust[i] = mlx_get_data_addr(game->bonust[i], &game->display.bits_per_pixel, &game->display.line_length, &game->display.endian);
		i++;
	}
}

void	ft_ray_texture(t_struct *game)
{
	if (game->ray.side == 0 && (game->ray.mapx < game->ray.posx))//PICK WALL
		game->tex.color = (int *)game->tex.n;
	else if (game->ray.side == 0 && (game->ray.mapx > game->ray.posx))
		game->tex.color = (int *)game->tex.s;
	else if (game->ray.side == 1 && (game->ray.mapy > game->ray.posy))
		game->tex.color = (int *)game->tex.e;
	else if (game->ray.side == 1 && (game->ray.mapy < game->ray.posy))
		game->tex.color = (int *)game->tex.w;
	if (game->ray.side == 0)//CHECK THE HIT POINT ON THE WALL
		game->tex.wall = game->ray.posy + game->ray.perpwalldist * game->ray.raydiry;
	else
		game->tex.wall = game->ray.posx + game->ray.perpwalldist * game->ray.raydirx;
	game->tex.wall -= floor((game->tex.wall));
	game->tex.x = (int)(game->tex.wall * game->tex.size);//CHECK THE POINT ON THE TEXTURE
	if (game->ray.side == 0 && game->ray.raydirx > 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	else if (game->ray.side == 1 && game->ray.raydiry < 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	game->tex.step = 1.0 * game->tex.size / game->ray.lineheight;
	game->tex.pos = (game->ray.drawstart - game->ray.ry / 2 + game->ray.lineheight / 2) * game->tex.step;
}

void	ft_ray_texture_bonus(t_struct *game)
{
	game->tex.color = (int *)game->bonust[game->bonusx];
	if (game->ray.side == 0)//CHECK THE HIT POINT ON THE WALL
		game->tex.wall = game->ray.posy + game->ray.perpwalldist * game->ray.raydiry;
	else
		game->tex.wall = game->ray.posx + game->ray.perpwalldist * game->ray.raydirx;
	game->tex.wall -= floor((game->tex.wall));
	game->tex.x = (int)(game->tex.wall * game->tex.size);//CHECK THE POINT ON THE TEXTURE
	if (game->ray.side == 0 && game->ray.raydirx > 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	else if (game->ray.side == 1 && game->ray.raydiry < 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	game->tex.step = 1.0 * game->tex.size / game->ray.lineheight;
	game->tex.pos = (game->ray.drawstart - game->ray.ry / 2 + game->ray.lineheight / 2) * game->tex.step;
}
