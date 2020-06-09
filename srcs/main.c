/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:17:49 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/03/15 15:30:59 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SDL_MAIN_HANDLED

#include <stdio.h>
#include "libft.h"
#include "SDL2/SDL.h"
#include "wolf3d.h"
#include <pthread.h>
#include <mspcoll.h>
#include <msputils.h>

#define SIZE_RECT            20

#define TIMEOUT_MILISEC        1000

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
	(void) event;
	(void) game;
	return (NO_ERR);
}

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

int render_level(t_game *game)
{
	int			x;
	int			y;
	SDL_Rect	rect;
	int			*pixels;
	int			pitch;

	SDL_LockTexture(game->texture, &rect, (void **) &pixels, &pitch);
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			++x;
		}
		++y;
	}
	SDL_UnlockTexture(game->texture);
	SDL_RenderCopy(game->rnd, game->texture, &rect, game->rect);
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

void render_game(t_game *game)
{
	SDL_SetRenderDrawColor(game->rnd, 0, 0, 0, 0);
	SDL_RenderClear(game->rnd);
	render_level(game);
	render_map(game);
	SDL_RenderPresent(game->rnd);
}

void process_game(t_game *game)
{
	(void) game;
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

void *func(void*arg)
{
	return (arg);
}

int create_window(t_game *game)
{
	pthread_t th;
	pthread_create(&th, NULL, func, NULL);
	game->rect = ft_memalloc(sizeof(SDL_Rect));
	if (!game->rect)
		return (MEM_ERR);
	game->rect->x = 0;
	game->rect->y = 0;
	game->rect->w = WIN_SIZE_W;
	game->rect->h = WIN_SIZE_H;
	game->wnd = SDL_CreateWindow(WIN_TITLE,
								 WIN_POS_X, WIN_POS_Y, WIN_SIZE_W, WIN_SIZE_H,
								 SDL_WINDOW_RESIZABLE);
	if (!game->wnd)
		return (SDL_ERR);
	game->rnd = SDL_CreateRenderer(game->wnd, 0, SDL_RENDERER_ACCELERATED |
												 SDL_RENDERER_PRESENTVSYNC);
	if (!game->rnd)
		return (SDL_ERR);
	game->texture = SDL_CreateTexture(game->rnd,
									  SDL_PIXELFORMAT_RGBA8888,
									  SDL_TEXTUREACCESS_STREAMING, WIN_SIZE_W,
									  WIN_SIZE_H);
	if (!game->texture)
		return (SDL_ERR);
	return (NO_ERR);
}

int destroy_window(t_game *game)
{
	SDL_DestroyTexture(game->texture);
	SDL_DestroyRenderer(game->rnd);
	SDL_DestroyWindow(game->wnd);
	ft_memdel((void **) &(game->rect));
	return (0);
}

int main(int argc, char **argv)
{
	t_game *game;

	SDL_Init(SDL_INIT_VIDEO);
	game = (t_game *) ft_memalloc(sizeof(*game));
	if (argc > 1)
		game->level = load_map_from_file(argv[1]);
	else
		return (0);
	if (create_window(game) != NO_ERR)
		return (SDL_ERR);
	game->state = G_MENU;
	event_loop(game);
	destroy_window(game);
	ft_memdel((void **) &game);
	SDL_Quit();
	return (0);
}
