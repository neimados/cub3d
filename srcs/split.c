/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:36 by dso               #+#    #+#             */
/*   Updated: 2022/04/18 11:25:21 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	freemalloc(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}

static int	ft_countwords(char const *str, char *c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(c, str[i]) && str[i])
		{
			count++;
			while (!ft_strchr(c, str[i]) && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_malloctab(char const *str, char *c, char **strs)
{	
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(c, str[i]))
			i++;
		else
		{
			while (!ft_strchr(c, str[i]) && str[i])
			{
				count++;
				i++;
			}
			strs[j] = malloc(sizeof(char) * (count + 1));
			if (!strs[j])
				return (freemalloc(strs));
			j++;
		}
	}
}

static void	ft_filltab(char const *str, char *c, char **strs, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (ft_strchr(c, str[i]) && str[i])
			i++;
		if (!ft_strchr(c, str[i]) && str[i])
		{
			while (!ft_strchr(c, str[i]) && str[i])
				strs[j][k++] = str[i++];
			strs[j][k] = '\0';
			k = 0;
			if (j < words)
				j++;
		}
	}
}

char	**ft_split(char *s, char *c)
{
	char	**strs;
	int		words;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	ft_malloctab(s, c, strs);
	ft_filltab(s, c, strs, words);
	strs[words] = NULL;
	return (strs);
}