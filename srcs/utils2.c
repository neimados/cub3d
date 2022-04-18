/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:13:30 by dso               #+#    #+#             */
/*   Updated: 2022/04/18 13:14:15 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strchr(const char *str, int c)
{
	c = (char)c;
	while (*str)
	{
		if (*str == c)
			return ((void *) str);
		str++;
	}
	if (c == '\0')
		return ((void *) str);
	return (NULL);
}

int	counttab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	minus;

	res = 0;
	minus = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
		if (res > 2147483648 && minus == -1)
			return (0);
		else if (res > 2147483647 && minus == 1)
			return (-1);
	}
	return (res * minus);
}

int	ft_check_digit(char **tmp2)
{
	int	i;
	int	j;

	i = 0;
	while (tmp2[i])
	{
		j = 0;
		while (tmp2[i][j])
		{
			if (!ft_isdigit(tmp2[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
