/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/06/18 16:25:52 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_bonus_xpm1(t_struct *game)
{
	if (game->bonust[0] == NULL)
		game->bonust[0] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus1.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[1] == NULL)
		game->bonust[1] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus2.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[2] == NULL)
		game->bonust[2] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus3.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[3] == NULL)
		game->bonust[3] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus4.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[4] == NULL)
		game->bonust[4] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus5.xpm", &game->tex.size, &game->tex.size);
}

void	ft_bonus_xpm2(t_struct *game)
{
	if (game->bonust[5] == NULL)
		game->bonust[5] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus6.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[6] == NULL)
		game->bonust[6] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus7.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[7] == NULL)
		game->bonust[7] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus8.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[8] == NULL)
		game->bonust[8] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus9.xpm", &game->tex.size, &game->tex.size);
	if (game->bonust[9] == NULL)
		game->bonust[9] = mlx_xpm_file_to_image(game->mlx,
				"./sprites/bonus10.xpm", &game->tex.size, &game->tex.size);
}

void	ft_init_bonus(t_struct *game)
{
	int	i;

	i = 0;
	ft_bonus_xpm1(game);
	ft_bonus_xpm2(game);
	while (i < 10)
	{
		if (!game->bonust[i])
		{
			ft_free_all(game);
			write(2, "Bonus texture failed\n", 15);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		game->bonust[i] = mlx_get_data_addr(game->bonust[i],
				&game->display.bits_per_pixel,
				&game->display.line_length, &game->display.endian);
		i++;
	}
}

void	ft_ray_texture_bonus(t_struct *game)
{
	game->tex.color = (int *)game->bonust[game->bonusx];
	if (game->ray.side == 0)
		game->tex.wall = game->ray.posy
			+ game->ray.perpwalldist * game->ray.raydiry;
	else
		game->tex.wall = game->ray.posx
			+ game->ray.perpwalldist * game->ray.raydirx;
	game->tex.wall -= floor((game->tex.wall));
	game->tex.x = (int)(game->tex.wall * game->tex.size);
	if (game->ray.side == 0 && game->ray.raydirx > 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	else if (game->ray.side == 1 && game->ray.raydiry < 0)
		game->tex.x = game->tex.size - game->tex.x - 1;
	game->tex.step = 1.0 * game->tex.size / game->ray.lineheight;
	game->tex.pos = (game->ray.drawstart - game->ray.ry / 2
			+ game->ray.lineheight / 2) * game->tex.step;
}

void	ft_ray_draw_bonus(t_struct *g)
{
	int	i;
	int	j;

	i = -1;
	j = g->ray.drawstart;
	while (++i < j)
	{
		g->tex.y = (int)g->tex.pos & (g->tex.size - 1);
		g->tex.pos += g->tex.step;
		g->display.addr[i * g->ray.rx + g->ray.x] = g->tex.color[g->tex.size
			* g->tex.y + g->tex.x];
	}
	while (j < g->ray.drawend)
	{
		g->tex.y = (int)g->tex.pos & (g->tex.size - 1);
		g->tex.pos += g->tex.step;
		g->display.addr[j * g->ray.rx + g->ray.x] = g->tex.color[g->tex.size
			* g->tex.y + g->tex.x];
		j++;
	}
	while (j < g->ray.ry)
	{
		g->display.addr[j * g->ray.rx + g->ray.x] = 0x00000000;
		j++;
	}
}
