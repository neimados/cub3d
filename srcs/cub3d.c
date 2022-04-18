/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/04/18 15:59:19 by dso              ###   ########.fr       */
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
	new.map.map = NULL;
	new.map.no = NULL;
	new.map.so = NULL;
	new.map.we = NULL;
	new.map.ea = NULL;
	new.map.sol = -1;
	new.map.plafond = -1;
	return (new);
}

int	ft_check_map_ext(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 5)
		return (1);
	if (filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		return (1);
	return (0);
}

long	ft_color_calc(char *tmp)
{
	char	**tmp2;
	int	i;
	int	r;
	int	g;
	int	b;
	
	i = 0;
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
	return ((r * 256 * 256) + (g * 256) + b);
}

int	ft_check_conf(t_struct *game)
{
	if (game->map.plafond == -1 || game->map.sol == -1)
		return (1);
	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea)
		return (1);
	return (0);
}

int	ft_check_duplicate(t_struct *game, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO"))
	{
		if (game->map.no)
			return (1);
		game->map.no = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "SO"))
	{
		if (game->map.so)
			return (1);
		game->map.so = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "WE"))
	{
		if (game->map.we)
			return (1);
		game->map.we = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "EA"))
	{
		if (game->map.ea)
			return (1);
		game->map.ea = ft_strdup(tmp[1]);
	}
	return (0);
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
		if (game->map.sol != -1)
			return (1);
		game->map.sol = ft_color_calc(tmp[1]);
		if (game->map.sol == -1)
			return (1);
	}
	else if (!ft_strcmp(tmp[0], "C"))
	{
		if (game->map.plafond != -1)
			return (1);
		game->map.plafond = ft_color_calc(tmp[1]);
		if (game->map.plafond == -1)
			return (1);
	}
	ft_free_tmp(tmp);
	return (ft_check_conf(game));
}

int	ft_parse(char *str, t_struct *game)
{
	int		i;
	char	**tmp;

	i = 0;
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
			if (ft_iswhitesp(str[i]) == 1 && !game->map.map)
				return (1);
			if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			{
				ft_strjoin(game->maptmp, str);
				ft_strjoin(game->maptmp, "\n");
				return (0);
			}
			i++;
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	game;
	
	if (argc != 1)
		return (ft_error("Error\nMap Error\n"));
	if (ft_check_map_ext(argv[1]) == 1)
		return (ft_error("Error\nIncorrect map extension\n"));
	if (ft_gnl(argv[1], &game) == 1)
		return (ft_error("Error\nIncorrect map\n"));
	game = ft_init_struct();
	
	// int	i = 0;
	// argc = 0;
	// (void)argv;
	// while (game.map.textures[i])
	// {
	// 	printf("TEST %s\n", game.map.textures[i]);
	// 	i++;
	// }
	

	return(0);
}
