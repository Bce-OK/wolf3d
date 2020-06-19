/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 22:57:01 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/19 23:26:19 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

unsigned int	get_wall_color(t_ray *ray, t_game *game, int y, int height)
{
	int				type;
	unsigned int	color;

	type = get_wall_type(ray, game);
	ray->wall_x -= (int)ray->wall_x;
	game->walls->num = type;
	color = get_texture_pixel(game->walls, ray->wall_x, y, height);
	return (color);
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