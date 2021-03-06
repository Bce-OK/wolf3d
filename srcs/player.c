/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:13:40 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/14 16:31:23 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

int		create_payer(t_game *game)
{
	t_numeric		size;

	size = 1.0;
	game->player = ft_memalloc(sizeof(t_player));
	game->player->pos_x = (game->level->startpos % game->level->size_x) * size;
	game->player->pos_x += size / 2;
	game->player->pos_y = (game->level->startpos / game->level->size_x) * size;
	game->player->pos_y += size / 2;
	game->player->prev_mouse_x = 0;
	game->player->watch_x = 1.0;
	game->player->watch_y = 0.0;
	return (NO_ERR);
}

void	move_player(t_game *game, t_numeric speed_x, t_numeric speed_y)
{
	int			next_x;
	int			next_y;
	t_numeric	speed;

	speed = game->player->is_running ? 1.0 : 3.0;
	next_x = (int)(game->player->pos_x + speed * speed_x);
	next_y = (int)(game->player->pos_y + speed * speed_y);
	if ((next_x != (int)game->player->pos_x)
	|| (next_y != (int)game->player->pos_y))
	{
		if (game->level->array[next_x + next_y * game->level->size_x])
			return ;
	}
	game->player->pos_x += speed * speed_x;
	game->player->pos_y += speed * speed_y;
}

void	rotate_player(const t_game *game, t_numeric speed)
{
	t_numeric			old_watch_x;
	t_numeric			angle;

	old_watch_x = game->player->watch_x;
	angle = (speed);
	game->player->watch_x = old_watch_x * cos(angle)
							- game->player->watch_y * sin(angle);
	game->player->watch_y = old_watch_x * sin(angle)
							+ game->player->watch_y * cos(angle);
}

void	destroy_player(t_game *game)
{
	ft_bzero((game->player), sizeof(t_player));
	ft_memdel((void**)&(game->player));
}
