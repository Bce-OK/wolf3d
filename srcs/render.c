/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:23:33 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 11:12:23 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

void	draw(t_game *game, int i, int column_h)
{
	int		space;
	int		r;

	r = 0;
	space = (game->rect->h - column_h) / 2;
	while(r < column_h && (r + 1 + space) < game->rect->h)
	{
		(game->pixels)[i + (r + space) * game->rect->w] =
			get_color_by_len(0xff0090ff, space, (int)(game->rect->h / 4));
		r++;
	}
}

void	start_ray(t_game *game, t_ray *ray, int x)
{
	numeric		camera_x;
	numeric		plane_x;
	numeric		plane_y;

	camera_x = 2 * x / (double)game->rect->w - 1;
	plane_x = game->player->watch_y;
	plane_y = -game->player->watch_x;
	ray->dir_x = game->player->watch_x + plane_x * camera_x;
	ray->dir_y = game->player->watch_y + plane_y * camera_x;
	ray->map_x = (int)game->player->pos_x;
	ray->map_y = (int)game->player->pos_y;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->perp_wall_dist = 0.0;
	ray->hit = 0;
	ray->side = 0;
}

void	step_check(t_game *game, t_ray *ray)
{
	if(ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->pos_x) * ray->delta_dist_x;
	}
	if(ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->pos_y) * ray->delta_dist_y;
	}
}

void	casting(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if ((ray->map_x >= game->level->size_x)
			|| (ray->map_y >= game->level->size_y)
			|| (game->level->array[ray->map_x + ray->map_y * game->level->size_x]))
			ray->hit = 1;
	}
}

void	render(t_game *game)
{
	int		x;
	t_ray	ray;
	int		lineHeight;

	x = 0;
	while (x < game->rect->w)
	{
		start_ray(game, &ray, x);
		step_check(game, &ray);
		casting(game, &ray);
		if(ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - game->player->pos_x + (1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - game->player->pos_y + (1 - ray.step_y) / 2) / ray.dir_y;
		if (ray.perp_wall_dist <= 1.0)
			lineHeight = game->rect->h;
		else
			lineHeight = (int)(game->rect->h / ray.perp_wall_dist);
		draw(game, x, lineHeight);
		x++;
	}
}

int		render_level(t_game *game)
{
	render(game);
	return (NO_ERR);
}