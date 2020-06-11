/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:20:21 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 20:31:41 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

unsigned int	get_color(unsigned char type)
{
	return ((type & 0x1u) |
		((255u * ((type & 0x2u) >> 1u)) << 8u) |
		((255u * ((type & 0x4u) >> 2u)) << 16u) |
		(0xffu << 24u));
}

void			render_rect(t_game *game, char type, int x, int y)
{
	SDL_Rect rect;
	unsigned color;

	rect.x = x * SIZE_RECT;
	rect.y = y * SIZE_RECT;
	rect.w = SIZE_RECT;
	rect.h = SIZE_RECT;
	color = get_color(type);
	SDL_SetRenderDrawColor(game->rnd, color & 0xffu,
						   (color & 0xff00u) >> 8u,
						   (color & 0xff0000u) >> 16u,
						   (color & 0xff000000u) >> 24u);
	SDL_RenderFillRect(game->rnd, &rect);
}

void			render_start_end(t_game *game)
{
	SDL_Rect	startpos;
	SDL_Rect	endpos;

	startpos.x = (game->level->startpos % game->level->size_x) * SIZE_RECT;
	startpos.y = (game->level->startpos / game->level->size_x) * SIZE_RECT;
	startpos.w = SIZE_RECT;
	startpos.h = SIZE_RECT;
	endpos.x = (game->level->endpos % game->level->size_x) * SIZE_RECT;
	endpos.y = (game->level->endpos / game->level->size_x) * SIZE_RECT;
	endpos.w = SIZE_RECT;
	endpos.h = SIZE_RECT;
	SDL_SetRenderDrawColor(game->rnd, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawRect(game->rnd, &startpos);
	SDL_SetRenderDrawColor(game->rnd, 0x90, 0x90, 0x90, 0xff);
	SDL_RenderFillRect(game->rnd, &endpos);
}

void			render_watch(t_game *game)
{
	int		x0;
	int		y0;
	int		xe;
	int		ye;

	x0 = (int)(game->player->pos_x / game->rect->h * (SIZE_RECT / 2));
	y0 = (int)(game->player->pos_y / game->rect->h * (SIZE_RECT / 2));
	xe = x0 + (int)(SIZE_RECT * cos(game->player->watch_x));
	ye = y0 + (int)(SIZE_RECT * sin(game->player->watch_x));
	SDL_SetRenderDrawColor(game->rnd, 0xff & 0xffu,
						   (0x70 & 0xff00u) >> 8u,
						   (0xa0 & 0xff0000u) >> 16u,
						   (0xff & 0xff000000u) >> 24u);
	SDL_RenderDrawLine(game->rnd, x0, y0, xe, ye);
	xe = x0 + (int)(SIZE_RECT * cos(game->player->watch_x - (FOV / 2.0)));
	ye = y0 + (int)(SIZE_RECT * sin(game->player->watch_x - (FOV / 2.0)));
	SDL_RenderDrawLine(game->rnd, x0, y0, xe, ye);
	xe = x0 + (int)(SIZE_RECT * cos(game->player->watch_x + (FOV / 2.0)));
	ye = y0 + (int)(SIZE_RECT * sin(game->player->watch_x + (FOV / 2.0)));
	SDL_RenderDrawLine(game->rnd, x0, y0, xe, ye);
}

void			render_map(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->level->size_x * game->level->size_y)
	{
		render_rect(game, (char) (game->level->array[i] & 0xff),
					i % game->level->size_x, i / game->level->size_x);
		++i;
	}
	render_start_end(game);
	render_watch(game);
}
