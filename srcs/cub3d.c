/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 09:46:32 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void start_game(t_struct	*game)
{
	game->map.mlx = mlx_init();
	game->map.win = mlx_new_window(game->map.mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D, work in progress");
	// game->map.img = ft_init_img();
	// ft_fill_img(game);
	ft_put_minimap(game);
	mlx_key_hook(game->map.win, key_hook, game);
	mlx_hook(game->map.win, 17, 1L << 17, ft_abort_prog, game);
	mlx_loop(game->map.mlx);
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
	player_pos(&game);
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
