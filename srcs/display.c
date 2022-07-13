/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:42:43 by dso               #+#    #+#             */
/*   Updated: 2022/06/28 10:11:37 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_ray(t_struct *game)
{
	if (game->player.direction == 'N')
	{
		game->ray.dirx = -1;
		game->ray.plany = 0.66;
	}
	else if (game->player.direction == 'S')
	{
		game->ray.dirx = 1;
		game->ray.plany = -0.66;
	}
	else if (game->player.direction == 'W')
	{
		game->ray.diry = -1;
		game->ray.planx = -0.66;
	}
	else if (game->player.direction == 'E')
	{
		game->ray.diry = 1;
		game->ray.planx = 0.66;
	}
}

void	ft_init_display(t_struct *game)
{
	game->display.img = NULL;
	game->display.addr = NULL;
	game->display.bits_per_pixel = 0;
	game->display.line_length = 0;
	game->display.endian = 0;
	game->display.img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	game->display.addr = (int *)mlx_get_data_addr(
		game->display.img,
		&game->display.bits_per_pixel,
		&game->display.line_length,
		&game->display.endian);
	game->ray.posx = (double)game->map.pos_x;
	game->ray.posy = (double)game->map.pos_y;
	game->ray.camerax = 0;
	game->ray.stepx = 0;
	game->ray.stepy = 0;
	game->ray.hit = 0;
	game->ray.side = 0;
	game->ray.perpwalldist = 0;
	game->ray.lineheight = 0;
	game->ray.drawstart = 0;
	game->ray.drawend = 0;
	game->ray.rx = MAP_WIDTH;
	game->ray.ry = MAP_HEIGHT;
	game->ray.speed = 0.03;
	game->ray.tspeed = 0.03;
}

void	ft_ray_step(t_struct *game)
{
	if (game->ray.raydirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidedistx = (game->ray.posx - game->ray.mapx) * game->ray.deltadistx;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidedistx = (game->ray.mapx + 1.0 - game->ray.posx) * game->ray.deltadistx;
	}
	if (game->ray.raydiry < 0)
	{
		game->ray.stepy = -1;
		game->ray.sidedisty = (game->ray.posy - game->ray.mapy) * game->ray.deltadisty;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidedisty = (game->ray.mapy + 1.0 - game->ray.posy) * game->ray.deltadisty;
	}
}

void	ft_ray_draw(t_struct *game)
{
	int	i;
	int	j;

	i = -1;
	j = game->ray.drawstart;
	while (++i < j)//DRAW PLAFOND
		game->display.addr[i * game->ray.rx + game->ray.x] = game->map.c;
	while (j < game->ray.drawend)//DRAW MURS
	{
		game->tex.y = (int)game->tex.pos & (game->tex.size - 1);
		game->tex.pos += game->tex.step;
		game->display.addr[j * game->ray.rx + game->ray.x] = game->tex.color[game->tex.size * game->tex.y + game->tex.x];
		j++;
	}
	while (j < game->ray.ry)//DRAW SOL
	{
		game->display.addr[j * game->ray.rx + game->ray.x] = game->map.f;
		j++;
	}
}

void	ft_ray_draw_bonus(t_struct *game)
{
	int	i;
	int	j;

	i = -1;
	j = game->ray.drawstart;
	while (++i < j)//DRAW PLAFOND
		game->display.addr[i * game->ray.rx + game->ray.x] = 0xFFFFFFFF;
	while (j < game->ray.drawend)//DRAW MURS
	{
		game->tex.y = (int)game->tex.pos & (game->tex.size - 1);
		game->tex.pos += game->tex.step;
		game->display.addr[j * game->ray.rx + game->ray.x] = game->tex.color[game->tex.size * game->tex.y + game->tex.x];
		j++;
	}
	while (j < game->ray.ry)//DRAW SOL
	{
		game->display.addr[j * game->ray.rx + game->ray.x] = 0xFFFFFFFF;
		j++;
	}
}

void	ft_ray_dda(t_struct *game)
{
	while (game->ray.hit == 0)//ENVOI DES RAYONS JUSQU A HIT
	{
		if (game->ray.sidedistx < game->ray.sidedisty)
		{
			game->ray.sidedistx += game->ray.deltadistx;
			game->ray.mapx += game->ray.stepx;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sidedisty += game->ray.deltadisty;
			game->ray.mapy += game->ray.stepy; 
			game->ray.side = 1;
		}
		if (game->map.map[game->ray.mapx][game->ray.mapy] == '1')
			game->ray.hit = 1;
	}
	//CALCUL DISTANCE AU MUR
	if (game->ray.side == 0)
		game->ray.perpwalldist = (game->ray.sidedistx - game->ray.deltadistx);
	else
		game->ray.perpwalldist = (game->ray.sidedisty - game->ray.deltadisty);
	//DISTANCE HAUTEUR
		game->ray.lineheight = (int)(game->ray.ry / game->ray.perpwalldist);
	game->ray.drawstart = -game->ray.lineheight / 2 + game->ray.ry / 2;
	if (game->ray.drawstart < 0)
		game->ray.drawstart = 0;
	game->ray.drawend = game->ray.lineheight / 2 + game->ray.ry / 2;
	if (game->ray.drawend >= game->ray.ry)
		game->ray.drawend = game->ray.ry - 1;
}

void	ft_ray_column(t_struct *game)
{
	game->ray.camerax = 2 * game->ray.x / (double)game->ray.rx - 1;
	game->ray.raydirx = game->ray.dirx + game->ray.planx * game->ray.camerax;
	game->ray.raydiry = game->ray.diry + game->ray.plany * game->ray.camerax;
	game->ray.mapx = game->map.pos_x;
	game->ray.mapy = game->map.pos_y;
	game->ray.deltadistx = fabs(1 / game->ray.raydirx);//FIX PB FISHEYE
	game->ray.deltadisty = fabs(1 / game->ray.raydiry);//FIX PB FISHEYE
	game->ray.hit = 0;
	ft_ray_step(game);
	ft_ray_dda(game);
	if (game->bonus == 1)
	{
		ft_ray_texture_bonus(game);
		ft_ray_draw_bonus(game);
	}
	else
	{
		ft_ray_texture(game);
		ft_ray_draw(game);
	}
}

void	ft_display(t_struct *game)
{
	ft_init_display(game);
	game->ray.x = 0;
	while (game->ray.x < game->ray.rx)
	{
		ft_ray_column(game);//PRINT PIXELS PAR COLONNES
		game->ray.x += 1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
}