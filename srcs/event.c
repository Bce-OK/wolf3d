/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:16:00 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 10:07:09 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

int event_keyup(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		game->state = G_QUIT;
	if ((event->key.keysym.sym == SDLK_w)
		|| (event->key.keysym.sym == SDLK_s)
		|| (event->key.keysym.sym == SDLK_d)
		|| (event->key.keysym.sym == SDLK_a))
		game->player->move = PM_NONE;
	return (NO_ERR);
}

int event_keydown(SDL_Event *event, t_game *game)
{
	(void) game;
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

int event_mouse(SDL_Event *event, t_game *game)
{
	numeric		old_watch_x;
	numeric		speed;

	old_watch_x = game->player->watch_x;
	speed = (event->motion.x - game->player->prev_mouse_x) * PLAYER_ROTATE;
	game->player->watch_x = game->player->watch_x * cos(speed)
		- game->player->watch_y * sin(speed);
	game->player->watch_y = old_watch_x * sin(speed)
		+ game->player->watch_y * cos(speed);
	game->player->prev_mouse_x = event->motion.x;
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
