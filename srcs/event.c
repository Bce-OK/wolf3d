/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:16:00 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 19:26:21 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

int		event_keyup(SDL_Event *event, t_game *game)
{
	if (game->state == G_PROCESS)
		return (event_keyup_process(event, game));
	if (game->state == G_MENU)
		return (event_keyup_menu(event, game));
	return (NO_ERR);
}

int		event_keydown(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_w)
		game->player->move = PM_FRONT;
	if (event->key.keysym.sym == SDLK_s)
		game->player->move = PM_BACK;
	if (event->key.keysym.sym == SDLK_d)
		game->player->move = PM_RIGHT;
	if (event->key.keysym.sym == SDLK_a)
		game->player->move = PM_LEFT;
	return (NO_ERR);
}

int		event_mouse(SDL_Event *event, t_game *game)
{
	if (game->state == G_PROCESS)
		return (event_mouse_process(event, game));
	if (game->state == G_MENU)
		return (event_mouse_menu(event, game));
	return (NO_ERR);
}

void	pool_all_events(t_game *game, SDL_Event *event)
{
	if (event->type == SDL_KEYUP)
		event_keyup(event, game);
	if (event->type == SDL_KEYDOWN)
		event_keydown(event, game);
	if (event->type == SDL_MOUSEMOTION)
		event_mouse(event, game);
	if (event->type == SDL_MOUSEBUTTONUP)
		event_mouse(event, game);
}

void	event_loop(t_game *game)
{
	SDL_Event	event;
	int			game_time;

	game_time = SDL_GetTicks();
	while (game->state != G_QUIT)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;
			pool_all_events(game, &event);
		}
		if ((SDL_GetTicks() - game_time) > TIMEOUT_MILISEC)
		{
			game->fps =  1000.0 / (SDL_GetTicks() - game_time);
			game_time = SDL_GetTicks();
			process_game(game);
		}
		render_game(game);
	}
}
