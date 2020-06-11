/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:23:33 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/12 01:27:04 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

/*
** закрашивание пикселей внутри поля зрения,
** на i-ой вертикали (шириной в два пикселя)
** размером column_h
*/
void	draw(t_game *game, int i, int column_h)
{
	int		space;
	int		r;

	r = 0;
	space = (game->rect->h - column_h) / 2;
	while (r < column_h && (r + 1 + space) < game->rect->h)
	{
		(game->pixels)[i * 2 + (r + space) * game->rect->w] =
			get_color_by_len(0xff0090ff, space, (int)(game->rect->h / 4));
		(game->pixels)[i * 2 + 1 + (r + space) * game->rect->w] =
			get_color_by_len(0xff9000ff, space, (int)(game->rect->h / 4));
		r++;
	}
}

/*
** Просчёт одной вертикали по углу game->player->watch_x + angle
** рассчёт расстояния до стены методом итераций по лучу
*/
void	casting(t_game *game, numeric angle, int i)
{
	numeric	t;
	numeric	cx;
	numeric	cy;
	int		column_h;

	t = RAY_STEP;
	while (t < END_RAY)
	{
		cx = game->player->pos_x + t * cos(angle);
		cy = game->player->pos_y + t * sin(angle);
		if (game->level->array[(int)cx + (int)cy * game->level->size_x] != 0)
		{
			column_h = (int)(game->rect->h /
				(t * cos(angle - game->player->watch_x)));
			if (column_h > game->rect->h)
				column_h = game->rect->h;
			draw(game, i, column_h);
			return ;
		}
		t += RAY_STEP;
	}
}

/*
** Отрисовка основного зрения камеры (всего угла обзора)
** из положения [game->player->pos_x, game_player_pos_y]
** повёрнутого на угол game->player->watch_x
** относительно прямого направления оси х
*/
void	render(t_game *game)
{
	numeric		angle;
	int	i;

	i = 0;
	while (i < game->rect->w / 2)
	{
		angle = game->player->watch_x - (FOV / 2.0)
				+ (FOV * i / (numeric)(game->rect->w / 2));
		casting(game, angle, i);
		i++;
	}
}

int		render_level(t_game *game)
{
	render(game);
	return (NO_ERR);
}