/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:17:49 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/03/12 21:47:18 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "SDL2/SDL.h"
#include "wolf3d.h"

int			event_keyup(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		game->state = G_QUIT;
	return (0);
}

int			event_keydown(SDL_Event *event, t_game *game)
{
	(void)event;
	(void)game;
	return (0);
}

int			event_mouse(SDL_Event *event, t_game *game)
{
	(void)event;
	(void)game;
	return (0);
}

void		render_game(t_game *game)
{
	(void)game;
}

void		event_loop(t_game *game)
{
	SDL_Event	event;

	while (game->state != G_QUIT)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
			if (event.type == SDL_KEYUP)
				event_keyup(&event, game);
			if (event.type == SDL_KEYDOWN)
				event_keydown(&event, game);
			if (event.type == SDL_MOUSEMOTION)
				event_mouse(&event, game);
		}
		render_game(game);
	}
}

int			create_window(t_game *game)
{
	game->wnd = SDL_CreateWindow(WIN_TITLE, WIN_POS_X, WIN_POS_Y, WIN_SIZE, WIN_SIZE
		, SDL_WINDOW_RESIZABLE);
	if (!game->wnd)
		return (SDL_ERR);
	game->rnd = SDL_CreateRenderer(game->wnd, 0, SDL_RENDERER_PRESENTVSYNC);
	if (!game->rnd)
		return (SDL_ERR);
	return (NO_ERR);
}

int			main(int argc, char **argv)
{
	t_game			*game;

	SDL_Init(SDL_INIT_VIDEO);
	game = (t_game*)ft_memalloc(sizeof(*game));
	if (argc > 1)
		game->level = load_map_from_file(argv[1]);
	else
		return (0);
	if (create_window(game) != NO_ERR)
		return (SDL_ERR);
	game->state = G_MENU;
	event_loop(game);
	ft_memdel((void**)&game);
	SDL_Quit();
	return (0);
}
