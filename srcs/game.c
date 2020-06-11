/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:14:16 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 16:22:52 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	render_game(t_game *game)
{
	SDL_SetRenderDrawColor(game->rnd, 255, 0, 0, 255);
	SDL_RenderClear(game->rnd);
	render_level(game);
	render_map(game);
	SDL_RenderPresent(game->rnd);
}

void	process_game(t_game *game)
{
	(void) game;
}

