/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:32:15 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 20:27:09 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

int		event_keyup_process(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		game->state = G_MENU;
		SDL_ShowCursor(1);
	}
	if ((event->key.keysym.sym == SDLK_w)
		|| (event->key.keysym.sym == SDLK_s)
		|| (event->key.keysym.sym == SDLK_d)
		|| (event->key.keysym.sym == SDLK_a))
		game->player->move = PM_NONE;
	return (NO_ERR);
}

int		event_mouse_process(SDL_Event *event, t_game *game)
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

void	render_process_game(t_game *game)
{
	render(game);
	render_map(game);
}

void	process_process_game(t_game *game)
{
	if (game->player->move == PM_FRONT)
	{
		game->player->pos_x += game->fps * PLAYER_MOVE * game->player->watch_x;
		game->player->pos_y += game->fps * PLAYER_MOVE * game->player->watch_y;
	}
	else if (game->player->move == PM_BACK)
	{
		game->player->pos_x -= game->fps * PLAYER_MOVE * game->player->watch_x;
		game->player->pos_y -= game->fps * PLAYER_MOVE * game->player->watch_y;
	}
	if (game->player->move == PM_RIGHT)
	{
		game->player->pos_x += game->fps * PLAYER_MOVE * game->player->watch_y;
		game->player->pos_y += game->fps * PLAYER_MOVE * game->player->watch_x;
	}
	else if (game->player->move == PM_LEFT)
	{
		game->player->pos_x -= game->fps * PLAYER_MOVE * game->player->watch_y;
		game->player->pos_y -= game->fps * PLAYER_MOVE * game->player->watch_x;
	}
	game->player->move = PM_NONE;
}