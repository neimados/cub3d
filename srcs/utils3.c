/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:11:19 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 12:32:02 by dso              ###   ########.fr       */
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
	new.player.x = 0;
	new.player.y = 0;
	new.player.dir_x = 0;
	new.player.dir_y = 0;
	return (new);
}
