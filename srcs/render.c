/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:23:33 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 18:46:45 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

void	draw(t_game *game, int **pixels, int i, int column_h)
{
	int	space;
	int r;

	r = 0;
	space = (game->rect->h - column_h) / 2;
	while(r < column_h && (r + 1 + space) < game->rect->h)
	{
		(*pixels)[i * 2 + (r + space) * game->rect->w] =
			get_color_by_len(255, space, game->rect->h);
		(*pixels)[i * 2 + 1 + (r + space) * game->rect->w] =
			get_color_by_len(255, space, game->rect->h);
		r++;
	}
}

void	casting(t_game *game, int **pixels, numeric angle, int i)
{
	numeric	t;
	numeric	cx;
	numeric	cy;
	int		column_h;

	t = RAY_STEP;
	while (t < 20.0)
	{
		cx = game->player->pos_x + t * cos(angle);
		cy = game->player->pos_y + t * sin(angle);
		if (game->level->array[(int)cx + (int)cy * game->level->size_x] != 0)
		{
			column_h = (int)(game->rect->h /
				(t * cos(angle - game->player->watch_x)));
			if (column_h > game->rect->h)
				column_h = game->rect->h;
			draw(game, pixels, i, column_h);
			return;
		}
		t += RAY_STEP;
	}
}

void	render(t_game *game, int **pixels)
{
	numeric		angle;
	int	i;

	i = 0;
	while (i < game->rect->w/ 2)
	{
		angle = game->player->watch_x - (FOV / 2.0)
				+ (FOV * i / (numeric)(game->rect->w / 2));
		casting(game, pixels, angle, i);
		i++;
	}
}

int		software_render(t_game *game)
{
	int			*pixels;

	SDL_LockSurface(game->surface);
	pixels = game->surface->pixels;
	ft_bzero(pixels, sizeof(int) * game->rect->w * game->rect->h);
	render(game, &pixels);
	SDL_UnlockSurface(game->surface);
	return (NO_ERR);
}

int		render_level(t_game *game)
{
	int			*pixels;
	int			pitch;

	if (game->is_software)
		return (software_render(game));
	SDL_LockTexture(game->texture, NULL, (void **) &pixels, &pitch);
	ft_bzero(pixels, sizeof(int) * game->rect->w * game->rect->h);
	render(game, &pixels);
	SDL_UpdateTexture(game->texture, NULL, pixels, pitch);
	SDL_UnlockTexture(game->texture);
	SDL_RenderCopy(game->rnd, game->texture, NULL, game->rect);
	return (NO_ERR);
}