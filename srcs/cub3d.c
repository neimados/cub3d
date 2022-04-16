/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/04/16 19:22:08 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

t_struct	ft_init_struct(void)
{
	t_struct	new;

	new.mlx = NULL;
	new.win = NULL;
	new.count = 0;
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

int	ft_parse(char *str, t_struct *game)
{
	
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
	return(0);
}
