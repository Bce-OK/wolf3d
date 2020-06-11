/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:17:49 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 16:24:44 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SDL_MAIN_HANDLED

#include "libft.h"
#include "wolf3d.h"

int main(int argc, char **argv)
{
	t_game *game;

	SDL_Init(SDL_INIT_VIDEO);
	game = (t_game *) ft_memalloc(sizeof(*game));
	if (argc > 1)
		game->level = load_map_from_file(argv[1]);
	else
		return (0);
	if (!game->level)
		return (MAP_ERR);
	if (create_window(game) != NO_ERR)
		return (SDL_ERR);
	if (create_payer(game) != NO_ERR)
		return (PLY_ERR);
	game->state = G_MENU;
	event_loop(game);
	destroy_window(game);
	ft_memdel((void **) &game);
	SDL_Quit();
	return (0);
}
