/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:13:40 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 20:23:46 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

int	create_payer(t_game *game)
{
	numeric		size;

	size = game->rect->h;
	game->player = ft_memalloc(sizeof(t_player));
	game->player->pos_x = (game->level->startpos % game->level->size_x) * size;
	game->player->pos_x += size / 2;
	game->player->pos_y = (game->level->startpos / game->level->size_x) * size;
	game->player->pos_y += size / 2;
	game->player->prev_mouse_x = 0;
	return (NO_ERR);
}