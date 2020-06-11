/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:20:21 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 16:20:21 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

void render_rect(t_game *game, char type, int x, int y)
{
	SDL_Rect rect;

	rect.x = x * SIZE_RECT;
	rect.y = y * SIZE_RECT;
	rect.w = SIZE_RECT;
	rect.h = SIZE_RECT;
	SDL_SetRenderDrawColor(game->rnd,
						   type & 0x1u, 255 * ((type & 0x2u) >> 1),
						   255 * ((type & 0x4u) >> 2), 0xff);
	SDL_RenderFillRect(game->rnd, &rect);
}

void render_map(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->level->size_x * game->level->size_y)
	{
		render_rect(game, (char) (game->level->array[i] & 0xff),
					i % game->level->size_x, i / game->level->size_x);
		++i;
	}
}
