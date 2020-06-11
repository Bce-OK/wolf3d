/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:14:16 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/12 00:43:26 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include "libft.h"

int		lock_render(t_game *game)
{
	int		err;

	err = 0;
	if (game->is_software)
	{
		if (SDL_MUSTLOCK(game->surface))
			err = SDL_LockSurface(game->surface);
		game->pixels = game->surface->pixels;
	}
	else
		err = SDL_LockTexture(game->texture,
			NULL, (void**)&game->pixels, &game->pitch);
	if (!err)
		ft_bzero(game->pixels,
		sizeof(int) * game->rect->w * game->rect->h);
	return (err);
}

void	unlock_render(t_game *game)
{
	if (game->is_software)
	{
		if (SDL_MUSTLOCK(game->surface))
			SDL_UnlockSurface(game->surface);
		SDL_UpdateWindowSurface(game->wnd);
	}
	else
	{
		SDL_UnlockTexture(game->texture);
		SDL_RenderCopy(game->rnd, game->texture, NULL, NULL);
		SDL_RenderPresent(game->rnd);
	}
}

void	render_game(t_game *game)
{
	lock_render(game);
	render_level(game);
	render_map(game);
	unlock_render(game);
}

void	process_game(t_game *game)
{
	if (game->player->move == PM_FRONT)
	{
		game->player->pos_x += PLAYER_SPEED * cos(game->player->watch_x);
		game->player->pos_y += PLAYER_SPEED * sin(game->player->watch_x);
	}
	else if (game->player->move == PM_BACK)
	{
		game->player->pos_x -= PLAYER_SPEED * cos(game->player->watch_x);
		game->player->pos_y -= PLAYER_SPEED * sin(game->player->watch_x);
	}
	if (game->player->move == PM_RIGHT)
	{
		game->player->pos_x += PLAYER_SPEED * sin(game->player->watch_x);
		game->player->pos_y += PLAYER_SPEED * cos(game->player->watch_x);
	}
	else if (game->player->move == PM_LEFT)
	{
		game->player->pos_x -= PLAYER_SPEED * sin(game->player->watch_x);
		game->player->pos_y -= PLAYER_SPEED * cos(game->player->watch_x);
	}
	game->player->move = PM_NONE;
}

