/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:56:26 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 09:49:25 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	*ft_gen_img(t_struct *game, char *s, int w, int h)
// {
// 	return (mlx_xpm_file_to_image(game->map.mlx, s, &w, &h));
// }

// static void	ft_destroy_img(t_struct *game)
// {
// 	if (game->map.img->ping)
// 		mlx_destroy_image(game->map.mlx, game->map.img->ping);
// 	if (game->map.img->min_floor)
// 		mlx_destroy_image(game->map.mlx, game->map.img->min_floor);
// 	if (game->map.img->min_wall)
// 		mlx_destroy_image(game->map.mlx, game->map.img->min_wall);
// 	free(game->map.img);
// }

// void	ft_fill_img(t_struct *game)
// {
// 	game->map.img->ping = ft_gen_img(game, "./img/min_ping.xpm", 16, 16);
// 	game->map.img->min_floor = ft_gen_img(game, "./img/min_floor.xpm", 16, 16);
// 	game->map.img->min_wall = ft_gen_img(game, "./img/min_wall.xpm", 32, 32);
// }

int	key_hook(int keycode, t_struct *game)
{
	printf("> %d\n", keycode);
	if (keycode == UP)
		printf("Move top"); // ft_move_perso(map, Y, -1, keycode);
	else if (keycode == DOWN)
		printf("Move down"); // ft_move_perso(map, Y, 1, keycode);
	else if (keycode == LEFT)
		printf("Move left"); // ft_move_perso(map, X, -1, keycode);
	else if (keycode == RIGHT)
		printf("Move right"); // ft_move_perso(map, X, 1, keycode);
	else if (keycode == TURN_RIGHT)
		printf("Turn right");
	else if (keycode == TURN_LEFT)
		printf("Turn left");
	else if (keycode == ESCAPE)
		ft_exit_prog(game, "Player escaped.");
	return (1);
}

void	ft_exit_prog(t_struct *game, char *str)
{
	(void)game;
	printf("Cub3d stopped: %s\n", str);
	// mlx_destroy_window(game->map.mlx, game->map.win);
	// ft_destroy_img(game);
	exit(0);
}

int	ft_abort_prog(t_struct *game)
{
	ft_exit_prog(game, "Window closed.");
	return (0);
}

// t_img	*ft_init_img(void)
// {
// 	t_img	*img;

// 	img = (t_img *)malloc(sizeof(t_img));
// 	if (!img)
// 		return (NULL);
// 	img->ping = NULL;
// 	img->min_floor = NULL;
// 	img->min_wall = NULL;
// 	img->north_texture = NULL;
// 	img->south_texturerefer = NULL;
// 	img->east_texture = NULL;
// 	img->west_texture = NULL;
// 	return (img);
// }
