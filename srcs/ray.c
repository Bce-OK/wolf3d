/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 22:57:01 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/14 21:06:33 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

unsigned int	get_wall_color(t_ray *ray, t_game *game)
{
	if (ray->side)
	{
		if (ray->map_y > game->player->pos_y)
			return (0xff909090);
		else
			return (0xffff9090);
	}
	else
	{
		if (ray->map_x > game->player->pos_x)
			return (0xff90ff90);
		else
			return (0xff9090ff);
	}
}


void			casting(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if ((ray->map_x >= game->level->size_x)
			|| (ray->map_y >= game->level->size_y
			|| (ray->map_x < 0 || ray->map_y < 0))
			|| (game->level->array[ray->map_x +
								   ray->map_y * game->level->size_x]))
			ray->hit = 1;
	}
}