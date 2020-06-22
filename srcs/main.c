/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:17:49 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/19 00:55:03 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SDL_MAIN_HANDLED

#include "libft.h"
#include "wolf3d.h"

int initialize(t_game *game)
{
	if (!game->level)
		return (MAP_ERR);
	if (create_window(game) != NO_ERR)
		return (SDL_ERR);
	if (create_payer(game) != NO_ERR)
		return (PLY_ERR);
	load_walls_texture(game, "res/wolftextures.bmp", 8);
	game->menu = create_menu(game);
	game->state = G_MENU;
	return (NO_ERR);
}

void finalize(t_game *game)
{
	destroy_menu(game);
	free_walls_texture(game);
	destroy_player(game);
	destroy_window(game);
	ft_memdel((void **) &(game->level));
	ft_memdel((void **) &game);
}

int thread_init(t_game *game) {
	int			status;
	SDL_Thread	*render_thread;

	game->mutex = SDL_CreateMutex();
	if (!game->mutex)
		return (NO_ERR);
	render_thread = SDL_CreateThread(render_loop, "render_loop", game);
	event_loop(game);
	SDL_WaitThread(render_thread, &status);
	SDL_DestroyMutex(game->mutex);
	return (status);
}

int main(int argc, char **argv)
{
	t_game	*game;
	int		err;

	SDL_Init(SDL_INIT_VIDEO);
	game = (t_game *) ft_memalloc(sizeof(*game));
	if (argc > 1)
		game->level = load_map_from_file(argv[1]);
	else
		return (0);
	if ((err = initialize(game)) != NO_ERR)
		return (err);
	thread_init(game);
	finalize(game);
	SDL_Quit();
	return (0);
}
