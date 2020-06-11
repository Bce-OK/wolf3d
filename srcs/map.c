/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:20:21 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 17:42:15 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

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
}
