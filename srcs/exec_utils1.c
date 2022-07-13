/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:56:26 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 16:03:31 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_key_press(int keycode, t_struct *game)
{
	if (keycode == UP)
		game->key_up = 1;
	else if (keycode == DOWN)
		game->key_down = 1;
	else if (keycode == RIGHT)
		game->key_right = 1;
	else if (keycode == LEFT)
		game->key_left = 1;
	else if (keycode == TURN_LEFT)
		game->key_turn_left = 1;
	else if (keycode == TURN_RIGHT)
		game->key_turn_right = 1;
	else
		return (0);
	return (1);
}

int	ft_key_release(int keycode, t_struct *game)
{
	if (keycode == UP)
		game->key_up = 0;
	else if (keycode == DOWN)
		game->key_down = 0;
	else if (keycode == RIGHT)
		game->key_right = 0;
	else if (keycode == LEFT)
		game->key_left = 0;
	else if (keycode == TURN_LEFT)
		game->key_turn_left = 0;
	else if (keycode == TURN_RIGHT)
		game->key_turn_right = 0;
	else if (keycode == TOUCHM)
	{
		if (game->minim == 0)
			game->minim = 1;
		else
			game->minim = 0;
	}
	else if (keycode == ESCAPE)
		ft_exit_prog(game, "Player escaped.");
	else
		return (0);
	return (1);
}

int	ft_get_keys(t_struct *game)
{
	double planxtmp;
	double dirxtmp;

	planxtmp = game->ray.planx;
	dirxtmp = game->ray.dirx;
	game->time += 1;
	if (game->time > 100)
	{
		if (game->key_turn_right == 1)//ROTATION DROITE
		{	
			game->ray.dirx = game->ray.dirx * cos(-game->ray.tspeed) - game->ray.diry * sin(-game->ray.tspeed);
			game->ray.diry = dirxtmp * sin(-game->ray.tspeed) + game->ray.diry * cos(-game->ray.tspeed);
			game->ray.planx = game->ray.planx * cos(-game->ray.tspeed) - game->ray.plany * sin(-game->ray.tspeed);
			game->ray.plany = planxtmp * sin(-game->ray.tspeed) + game->ray.plany * cos(-game->ray.tspeed);
		}
		if (game->key_turn_left == 1)//ROTATION GAUCHE
		{
			game->ray.dirx = game->ray.dirx * cos(game->ray.tspeed) - game->ray.diry * sin(game->ray.tspeed);
			game->ray.diry = dirxtmp * sin(game->ray.tspeed) + game->ray.diry * cos(game->ray.tspeed);
			game->ray.planx = game->ray.planx * cos(game->ray.tspeed / 2) - game->ray.plany * sin(game->ray.tspeed);
			game->ray.plany = planxtmp * sin(game->ray.tspeed) + game->ray.plany * cos(game->ray.tspeed);
		}
		if (game->key_up == 1)//ALLER TOUT DROIT
		{
			if (game->map.map[(int)(game->map.pos_x + (game->ray.dirx * game->ray.speed * 2))][(int)game->map.pos_y] == '0')
				game->map.pos_x += game->ray.dirx * game->ray.speed;
			if (game->map.map[(int)(game->map.pos_x)][(int)(game->map.pos_y + (game->ray.diry * game->ray.speed * 2))] == '0')
				game->map.pos_y += game->ray.diry * game->ray.speed;
		}
		if (game->key_down == 1)//RECULER
		{
			if (game->map.map[(int)(game->map.pos_x - (game->ray.dirx * game->ray.speed * 2))][(int)(game->map.pos_y)] == '0')
			game->map.pos_x -= game->ray.dirx * game->ray.speed;
			if (game->map.map[(int)(game->map.pos_x)][(int)(game->map.pos_y - (game->ray.diry * game->ray.speed * 2))] == '0')
				game->map.pos_y -= game->ray.diry * game->ray.speed;
		}
		if (game->key_right == 1)//PAS A DROITE
		{
			if (game->map.map[(int)(game->map.pos_x + game->ray.diry * (game->ray.speed * 2))][(int)game->map.pos_y] == '0')
				game->map.pos_x += game->ray.diry * game->ray.speed;
			if (game->map.map[(int)game->ray.posx][(int)(game->ray.posy - game->ray.dirx * (game->ray.speed * 2))] == '0')
				game->map.pos_y -= game->ray.dirx * game->ray.speed;
		}
		if (game->key_left == 1)//PAS A GAUCHE
		{
			if (game->map.map[(int)(game->map.pos_x - game->ray.diry * (game->ray.speed * 2))][(int)game->map.pos_y] == '0')
				game->map.pos_x -= game->ray.diry * game->ray.speed;
			if (game->map.map[(int)game->map.pos_x][(int)(game->map.pos_y + game->ray.dirx * (game->ray.speed * 2))] == '0')
				game->map.pos_y += game->ray.dirx * game->ray.speed;
		}
		game->time = 0;
		ft_display(game);
		if (game->minim == 1)
			ft_put_minimap(game);
		mlx_destroy_image(game->mlx, game->display.img);
	}
	return (1);
}

void	ft_exit_prog(t_struct *game, char *str)
{
	(void)game;
	printf("Cub3d stopped: %s\n", str);
	exit(0);
}

int	ft_abort_prog(t_struct *game)
{
	ft_exit_prog(game, "Window closed.");
	return (0);
}
