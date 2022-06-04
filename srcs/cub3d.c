/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/06/04 11:53:01 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_struct	ft_init_struct(void)
{
	t_struct	new;

	new.mlx = NULL;
	new.win = NULL;
	new.count = 0;
	new.pos = 0;
	new.maptmp = NULL;
	new.map.map = NULL;
	new.map.no = NULL;
	new.map.so = NULL;
	new.map.we = NULL;
	new.map.ea = NULL;
	new.map.f = -1;
	new.map.c = -1;
	new.player.x = 0;
	new.player.y = 0;
	return (new);
}

long	ft_color_calc(char *tmp)
{
	char	**tmp2;
	int	r;
	int	g;
	int	b;

	tmp2 = ft_split(tmp, " \t\n\v\f\r,");
	if (!tmp2 || counttab(tmp2) != 3)
	{
		ft_free_tmp(tmp2);
		return (-1);
	}
	if (ft_check_digit(tmp2) == 1)
		return (-1);
	r = ft_atoi(tmp2[0]);
	g = ft_atoi(tmp2[1]);
	b = ft_atoi(tmp2[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	ft_free_tmp(tmp2);
	return ((r * 256 * 256) + (g * 256) + b);
}

int	ft_fillconf(t_struct *game, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO") || !ft_strcmp(tmp[0], "SO")
	|| !ft_strcmp(tmp[0], "WE") || !ft_strcmp(tmp[0], "EA"))
	{
		if (ft_check_duplicate(game, tmp) == 1)
			return (1);
	}
	else if (!ft_strcmp(tmp[0], "F"))
	{
		if (game->map.f != -1)
			return (1);
		game->map.f = ft_color_calc(tmp[1]);
		if (game->map.f == -1)
			return (1);
	}
	else if (!ft_strcmp(tmp[0], "C"))
	{
		if (game->map.c != -1)
			return (1);
		game->map.c = ft_color_calc(tmp[1]);
		if (game->map.c == -1)
			return (1);
	}
	ft_free_tmp(tmp);
	return (0);
}

int	ft_parse(char *str, t_struct *game)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (game->count != 6)
	{
		while (str[i] && (ft_iswhitesp(str[i]) == 1 || str[i] == ' '))
			i++;
		if (str[i])
		{
			game->count += 1;
			tmp = ft_split(str, " \t\n\v\f\r");
			if (!tmp || counttab(tmp) != 2)
				return (ft_free_parse(game, tmp));
			if (ft_fillconf(game, tmp) == 1)
				return (ft_free_parse(game, tmp));
			return (0);
		}
	}
	else
	{
		while (str[i])
		{
			if (game->pos != 0)
				if (ft_iswhitesp(str[0]) == 1)
					str[0] = 'x';
			if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
				game->pos = 1;
			i++;
		}
		if (game->pos != 0)
		{
			game->maptmp = ft_strjoin(game->maptmp, str);
			if (!game->maptmp)
				return (ft_free_parse(game, tmp));
			return (0);
		}
	}
	return (0);
}

int	ft_gnl(char *av, t_struct *game)
{
	int		fd;
	char	*str;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (1);
	str = get_next_line(fd);
	if (!str)
		return (1);
	while (str)
	{
		if (ft_parse(str, game) == 1)
		{
			free(str);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
	}
	game->map.map = ft_split(game->maptmp, "\n");
	free(game->maptmp);
	if (!game->map.map)
		return (1);
	return (0);
}

void	player_pos(t_struct *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
			|| game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				printf("POSITION %c \n", game->map.map[i][j]);
				game->player.x = j;
				game->player.y = i;
				game->player.direction = game->map.map[i][j];
				game->map.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
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

	return(0);
}
