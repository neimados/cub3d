/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:11:19 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 16:04:05 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
}

void	ft_init_struct2(t_struct *new)
{
	int	i;

	i = -1;
	new->player.x = 0;
	new->player.y = 0;
	new->minim = 0;
	new->bonus = 0;
	new->bonusx = 0;
	new->tex.n = NULL;
	new->tex.s = NULL;
	new->tex.e = NULL;
	new->tex.w = NULL;
	while (new->bonust[++i])
		new->bonust[i] = NULL;
}

t_struct	ft_init_struct(void)
{
	t_struct	new;

	new.time = 0;
	new.key_up = 0;
	new.key_down = 0;
	new.key_right = 0;
	new.key_left = 0;
	new.key_turn_left = 0;
	new.key_turn_left = 0;
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
	ft_init_struct2(&new);
	return (new);
}

int	ft_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_map_width(char **map)
{
	int	i;
	int	max;
	int	tmp;

	i = 0;
	max = 0;
	tmp = 0;
	while (map[i])
	{
		tmp = ft_strlen(map[i]);
		if (tmp > max)
			max = tmp;
		i++;
	}
	return (max);
}
