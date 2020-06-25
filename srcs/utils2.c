/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:28:45 by wpoudre           #+#    #+#             */
/*   Updated: 2020/06/25 16:28:48 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

SDL_Point	set_to(int x, int y)
{
	SDL_Point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void		fill_rect(unsigned int *pixels, SDL_Rect *view,
		SDL_Rect *rect, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	if (rect->x + rect->w > view->w || rect->x < 0
			|| rect->y + rect->h > view->h || rect->y < 0)
		return ;
	while (y < rect->h)
	{
		x = 0;
		while (x < rect->w)
		{
			pixels[rect->x + x + (rect->y + y) * view->w] = color;
			++x;
		}
		++y;
	}
}

SDL_Rect	create_rect(int x, int y, int w, int h)
{
	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}
