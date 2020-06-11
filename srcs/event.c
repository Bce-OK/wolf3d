/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:16:00 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 20:28:41 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#define TIMEOUT_MILISEC     1000

int event_keyup(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		game->state = G_QUIT;
	return (NO_ERR);
}

int event_keydown(SDL_Event *event, t_game *game)
{
	(void) event;
	(void) game;
	return (NO_ERR);
}

int event_mouse(SDL_Event *event, t_game *game)
{
	if (event && event->type == SDL_MOUSEMOTION)
	{
		if (event->motion.x != 0)
		{
			game->player->watch_x +=
				(game->player->prev_mouse_x - event->motion.x) * 0.025;
			game->player->prev_mouse_x = event->motion.x;
		}
	}
	return (NO_ERR);
}

void event_loop(t_game *game)
{
	SDL_Event event;
	int game_time;

	game_time = SDL_GetTicks();
	while (game->state != G_QUIT)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;
			if (event.type == SDL_KEYUP)
				event_keyup(&event, game);
			if (event.type == SDL_KEYDOWN)
				event_keydown(&event, game);
			if (event.type == SDL_MOUSEMOTION)
				event_mouse(&event, game);
		}
		if (SDL_GetTicks() - game_time > TIMEOUT_MILISEC)
		{
			game_time = SDL_GetTicks();
			process_game(game);
		}
		render_game(game);
	}
}
