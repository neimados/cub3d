/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:46:37 by dvergobb          #+#    #+#             */
/*   Updated: 2022/06/28 13:16:48 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void start_game(t_struct *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D, work in progress");
	ft_put_minimap(game);
	mlx_loop_hook(game->mlx, ft_get_keys, game);
	mlx_hook(game->win, 17, 1L << 17, ft_abort_prog, game);
	mlx_hook(game->win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, ft_key_release, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_struct	game;

	game = ft_init_struct();
	if (argc != 2)
		return (ft_error("Error\nMap Error\n"));
	if (ft_check_map_ext(argv[1]) == 1)
		return (ft_error("Error\nIncorrect map extension\n"));
	if (ft_gnl(argv[1], &game) == 1)
		return (ft_error("Error\nFile incorrect\n"));
	if (ft_check_conf(&game) == 1)
		return (ft_error("Error\nIncorrect map configuration\n"));
	if (ft_check_map(&game) == 1)
		return (ft_error("Error\nMap is not valid\n"));
	player_pos(&game, -1, -1);
	start_game(&game);
	
/*
//TEST BEGIN
	printf("NO %s\n", game.map.no);
	printf("SO %s\n", game.map.so);
	printf("WE %s\n", game.map.we);
	printf("EA %s\n", game.map.ea);
	printf("F %ld\n", game.map.f);
	printf("C %ld\n", game.map.c);

	printf("PLAYER X %d\n", game.player.x);
	printf("PLAYER Y %d\n", game.player.y);
	printf("DIRECTION %c\n", game.player.direction);

	int	i = 0;
	while (game.map.map[i])
	{
		printf("MAP %s\n", game.map.map[i]);
		i++;
	}
//TEST END
*/

	return (0);
}
