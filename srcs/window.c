/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:15:03 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 21:54:32 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

int		create_renderer(t_game *game, int is_software)
{
	game->is_software = is_software;
	game->surface = SDL_GetWindowSurface(game->wnd);
	if (!game->surface)
		return (SDL_ERR);
	if (game->is_software)
		game->rnd = SDL_CreateSoftwareRenderer(game->surface);
	else
		game->rnd = SDL_CreateRenderer
			(game->wnd, 0,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!game->rnd)
		return (SDL_ERR);
	return (NO_ERR);
}

int		create_window(t_game *game)
{
	game->rect = ft_memalloc(sizeof(SDL_Rect));
	if (!game->rect)
		return (MEM_ERR);
	game->rect->x = 0;
	game->rect->y = 0;
	game->rect->w = WIN_SIZE_W;
	game->rect->h = WIN_SIZE_H;
	game->wnd = SDL_CreateWindow(WIN_TITLE,
					 WIN_POS_X, WIN_POS_Y, WIN_SIZE_W, WIN_SIZE_H,
					 SDL_WINDOW_OPENGL);
	if (!game->wnd)
		return (SDL_ERR);
	if (create_renderer(game, SOFTWARE) != NO_ERR)
		return (SDL_ERR);
	game->texture = SDL_CreateTexture(game->rnd, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_SIZE_W, WIN_SIZE_H);
	if (!game->texture)
		return (SDL_ERR);
	SDL_SetRelativeMouseMode(1);
	return (NO_ERR);
}

int destroy_window(t_game *game)
{
	SDL_SetRelativeMouseMode(0);
	SDL_DestroyTexture(game->texture);
	SDL_DestroyRenderer(game->rnd);
	SDL_FreeSurface(game->surface);
	SDL_DestroyWindow(game->wnd);
	ft_memdel((void **) &(game->rect));
	return (0);
}
