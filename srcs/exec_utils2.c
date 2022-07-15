/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dso@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:56:26 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 16:03:31 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_rotate_left(t_struct *game)
{
	double	planxtmp;
	double	dirxtmp;

	planxtmp = game->ray.planx;
	dirxtmp = game->ray.dirx;
	if (game->key_turn_left == 1)
	{
		game->ray.dirx = game->ray.dirx * cos(game->ray.tspeed)
			- game->ray.diry * sin(game->ray.tspeed);
		game->ray.diry = dirxtmp * sin(game->ray.tspeed)
			+ game->ray.diry * cos(game->ray.tspeed);
		game->ray.planx = game->ray.planx * cos(game->ray.tspeed / 2)
			- game->ray.plany * sin(game->ray.tspeed);
		game->ray.plany = planxtmp * sin(game->ray.tspeed)
			+ game->ray.plany * cos(game->ray.tspeed);
	}
}

void	ft_rotate_right(t_struct *game)
{
	double	planxtmp;
	double	dirxtmp;

	planxtmp = game->ray.planx;
	dirxtmp = game->ray.dirx;
	if (game->key_turn_right == 1)
	{	
		game->ray.dirx = game->ray.dirx * cos(-game->ray.tspeed)
			- game->ray.diry * sin(-game->ray.tspeed);
		game->ray.diry = dirxtmp * sin(-game->ray.tspeed)
			+ game->ray.diry * cos(-game->ray.tspeed);
		game->ray.planx = game->ray.planx * cos(-game->ray.tspeed)
			- game->ray.plany * sin(-game->ray.tspeed);
		game->ray.plany = planxtmp * sin(-game->ray.tspeed)
			+ game->ray.plany * cos(-game->ray.tspeed);
	}
}

void	ft_move(t_struct *game)
{
	if (game->key_up == 1)
	{
		if (game->map.map[(int)(game->map.pos_x + (game->ray.dirx
					* game->ray.speed * 2))][(int)game->map.pos_y] == '0')
			game->map.pos_x += game->ray.dirx * game->ray.speed;
		if (game->map.map[(int)(game->map.pos_x)][(int)(game->map.pos_y
			+ (game->ray.diry * game->ray.speed * 2))] == '0')
			game->map.pos_y += game->ray.diry * game->ray.speed;
	}
	if (game->key_down == 1)
	{
		if (game->map.map[(int)(game->map.pos_x - (game->ray.dirx
					* game->ray.speed * 2))][(int)(game->map.pos_y)] == '0')
			game->map.pos_x -= game->ray.dirx * game->ray.speed;
		if (game->map.map[(int)(game->map.pos_x)][(int)(game->map.pos_y
			- (game->ray.diry * game->ray.speed * 2))] == '0')
			game->map.pos_y -= game->ray.diry * game->ray.speed;
	}
}

void	ft_left_right(t_struct *game)
{
	if (game->key_right == 1)
	{
		if (game->map.map[(int)(game->map.pos_x + game->ray.diry
				* (game->ray.speed * 2))][(int)game->map.pos_y] == '0')
			game->map.pos_x += game->ray.diry * game->ray.speed;
		if (game->map.map[(int)game->ray.posx][(int)(game->ray.posy
			- game->ray.dirx * (game->ray.speed * 2))] == '0')
			game->map.pos_y -= game->ray.dirx * game->ray.speed;
	}
	if (game->key_left == 1)
	{
		if (game->map.map[(int)(game->map.pos_x - game->ray.diry
				* (game->ray.speed * 2))][(int)game->map.pos_y] == '0')
			game->map.pos_x -= game->ray.diry * game->ray.speed;
		if (game->map.map[(int)game->map.pos_x][(int)(game->map.pos_y
			+ game->ray.dirx * (game->ray.speed * 2))] == '0')
			game->map.pos_y += game->ray.dirx * game->ray.speed;
	}
}

int	ft_abort_prog(t_struct *game)
{
	ft_exit_prog(game, "Window closed.");
	return (0);
}
