/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:56:26 by dvergobb          #+#    #+#             */
/*   Updated: 2022/07/20 11:41:18 by dvergobb         ###   ########.fr       */
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

void	ft_key_release2(int keycode, t_struct *game)
{
	if (keycode == TOUCHM)
	{
		if (game->minim == 0)
			game->minim = 1;
		else
			game->minim = 0;
	}
	else if (keycode == TOUCHX)
	{
		if (game->bonus == 0)
			game->bonus = 1;
		else
			game->bonus = 0;
	}
	else if (keycode == ESCAPE)
		ft_exit_prog(game, "Player escaped.");
}

int	ft_key_release(int keycode, t_struct *game)
{
	ft_key_release2(keycode, game);
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
	else
		return (0);
	return (1);
}

int	ft_get_keys(t_struct *game)
{
	game->time += 1;
	if (game->time > 300)
	{
		ft_rotate_left(game);
		ft_rotate_right(game);
		ft_move(game);
		ft_left_right(game);
		game->time = 0;
		ft_display(game);
		if (game->minim == 1)
			ft_put_minimap(game, -2, -2);
		mlx_destroy_image(game->mlx, game->display.img);
		if (game->bonusx >= 3)
			game->bonusx = 0;
		else
			game->bonusx += 1;
	}
	return (1);
}

void	ft_exit_prog(t_struct *game, char *str)
{
	(void)game;
	printf("Cub3d stopped: %s\n", str);
	exit(0);
}
