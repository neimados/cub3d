/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/07/20 09:36:58 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_ray(t_struct *game)
{
	if (game->player.direction == 'N')
	{
		game->ray.dirx = -1;
		game->ray.plany = 0.66;
	}
	else if (game->player.direction == 'S')
	{
		game->ray.dirx = 1;
		game->ray.plany = -0.66;
	}
	else if (game->player.direction == 'W')
	{
		game->ray.diry = -1;
		game->ray.planx = -0.66;
	}
	else if (game->player.direction == 'E')
	{
		game->ray.diry = 1;
		game->ray.planx = 0.66;
	}
}

static void	ft_init_display2(t_struct *game)
{
	game->ray.camerax = 0;
	game->ray.stepx = 0;
	game->ray.stepy = 0;
	game->ray.hit = 0;
	game->ray.side = 0;
	game->ray.perpwalldist = 0;
	game->ray.lineheight = 0;
	game->ray.drawstart = 0;
	game->ray.drawend = 0;
	game->ray.rx = MAP_WIDTH;
	game->ray.ry = MAP_HEIGHT;
	game->ray.speed = 0.09;
	game->ray.tspeed = 0.09;
}

void	ft_init_display(t_struct *game)
{
	game->display.img = NULL;
	game->display.addr = NULL;
	game->display.bits_per_pixel = 0;
	game->display.line_length = 0;
	game->display.endian = 0;
	game->display.img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	game->display.addr = (int *)mlx_get_data_addr(
			game->display.img,
			&game->display.bits_per_pixel,
			&game->display.line_length,
			&game->display.endian);
	game->ray.posx = (double)game->map.pos_x;
	game->ray.posy = (double)game->map.pos_y;
	ft_init_display2(game);
}

static void	ft_ray_step2(t_struct *game)
{
	if (game->ray.raydiry < 0)
	{
		game->ray.stepy = -1;
		game->ray.sidedisty = (game->ray.posy - game->ray.mapy)
			* game->ray.deltadisty;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidedisty = (game->ray.mapy + 1.0 - game->ray.posy)
			* game->ray.deltadisty;
	}
}

void	ft_ray_step(t_struct *game)
{
	if (game->ray.raydirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidedistx = (game->ray.posx - game->ray.mapx)
			* game->ray.deltadistx;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidedistx = (game->ray.mapx + 1.0 - game->ray.posx)
			* game->ray.deltadistx;
	}
	ft_ray_step2(game);
}
