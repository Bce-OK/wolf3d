/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:14:16 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/14 11:49:47 by hgreenfe         ###   ########.fr       */
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
		game->pitch = game->surface->pitch;
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
	if (game->state == G_PROCESS || game->state == G_PAUSE)
		render_process_game(game);
	if (game->state == G_MENU)
		render_menu_game(game);
	if (game->state == G_EDITOR)
		render_editor_game(game);
	unlock_render(game);
}

void	process_game(t_game *game)
{
	if (game->state == G_PROCESS)
		process_process_game(game);
	if (game->state == G_MENU)
		process_menu_game(game);
	if (game->state == G_EDITOR)
		process_editor_game(game);
	print_str(game, set_to(game->rect->w - game->font->letter_w * 3, 100),
		game->font, ft_itoa(game->fps));
}

