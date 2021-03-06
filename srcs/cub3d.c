/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:34:05 by dvergobb          #+#    #+#             */
/*   Updated: 2022/07/20 11:37:11 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	start_game(t_struct *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	ft_init_ray(game);
	ft_init_textures(game);
	mlx_hook(game->win, 17, 1L << 17, ft_abort_prog, game);
	mlx_hook(game->win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_release, game);
	mlx_loop_hook(game->mlx, ft_get_keys, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_struct	game;

	game = ft_init_struct();
	if (argc != 2)
		ft_error("Error\nMap Error\n");
	if (ft_check_map_ext(argv[1]) == 1)
		ft_error("Error\nIncorrect map extension\n");
	if (ft_gnl(argv[1], &game) == 1)
		ft_error("Error\nFile incorrect\n");
	if (ft_check_conf(&game) == 1)
		ft_error("Error\nIncorrect map configuration\n");
	if (ft_check_map(&game) == 1)
		ft_error("Error\nMap is not valid\n");
	player_pos(&game, 0, 0);
	game.map.height = ft_map_height(game.map.map);
	game.map.width = ft_map_width(game.map.map);
	game.map.pos_x = game.player.y + 0.2;
	game.map.pos_y = game.player.x + 0.2;
	start_game(&game);
	return (0);
}
