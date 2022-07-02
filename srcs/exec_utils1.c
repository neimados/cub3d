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
	else if (keycode == ESCAPE)
		ft_exit_prog(game, "Player escaped.");
	else
		return (0);
	return (1);
}

int	ft_get_keys(t_struct *game)
{
	double	inc = 0.1;
	int		x;
	int		y;

	x = game->map.pos_x;
	y = game->map.pos_y;
	game->time += 1;
	if (game->time > 100)
	{
		if (game->key_turn_left == 1)
			printf("Turn left\n");
		if (game->key_turn_right == 1)
			printf("Turn right\n");
		if (game->key_up == 1)
		{
			game->map.pos_y -= inc;
			y = game->map.pos_y;
			if (game->map.map[y][x] != '0')
				game->map.pos_y += inc;
			printf("Go up\n");
		}
		if (game->key_down == 1)
		{
			game->map.pos_y += inc;
			y = game->map.pos_y;
			if (game->map.map[y][x] != '0')
				game->map.pos_y -= inc;
			printf("Go down\n");
		}
		if (game->key_right == 1)
		{
			game->map.pos_x += inc;
			x = game->map.pos_x;
			if (game->map.map[y][x] != '0')
				game->map.pos_x -= inc;
			printf("Go right\n");
		}
		if (game->key_left == 1)
		{
			game->map.pos_x -= inc;
			x = game->map.pos_x;
			if (game->map.map[y][x] != '0')
				game->map.pos_x += inc;
			printf("Go left\n");
		}
		game->time = 0;
		ft_display(game);
		ft_put_minimap(game);
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
