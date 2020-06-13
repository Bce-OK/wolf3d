/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:32:38 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 19:06:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		event_keyup_menu(SDL_Event *event, t_game *game)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		if (game->state == G_MENU)
			game->state = G_QUIT;
	}
	if (event->key.keysym.sym == SDLK_RETURN)
		game->state = G_PROCESS;
}
int		event_mouse_menu(SDL_Event *event, t_game *game)
{
	SDL_Point	cursor;
	SDL_Rect	start_game_rect;

	if ( event->type == SDL_MOUSEBUTTONUP
	&& event->button.state == SDL_BUTTON_LEFT)
	{
		start_game_rect.x = game->rect->w / 2 - game->font->letter_w * 2;
		start_game_rect.y = 100;
		start_game_rect.w = game->font->letter_w * 4;
		start_game_rect.h = game->font->letter_h;
		cursor = set_to(event->motion.x, event->motion.y);
		if (SDL_PointInRect(&cursor, &start_game_rect))
		{
			game->state = G_PROCESS;
			SDL_SetRelativeMouseMode(1);
		}
	}
}

int		render_menu_game(t_game *game)
{
	int		menu_pos_x;
	int		menu_pos_y;

	SDL_RenderSetScale(game->rnd, 0.5f, 0.5f);
	menu_pos_x = game->rect->w / 2 - game->font->letter_w * 2;
	menu_pos_y = 100;
	print_str(game, set_to(menu_pos_x, menu_pos_y), game->font, "GAME");
	menu_pos_x = game->rect->w / 2 - game->font->letter_w * 5;
	menu_pos_y += game->font->letter_h * 3 / 2;
	print_str(game, set_to(menu_pos_x, menu_pos_y), game->font, "MAP_EDITOR");
	menu_pos_x = game->rect->w / 2 - game->font->letter_w * 2;
	menu_pos_y += game->font->letter_h * 3 / 2;
	print_str(game, set_to(menu_pos_x, menu_pos_y), game->font, "QUIT");
	return (NO_ERR);
}

void	process_menu_game(t_game *game)
{
	SDL_SetRelativeMouseMode(1);
}