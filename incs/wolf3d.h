/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:52:31 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/13 23:02:01 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
#include "SDL2/SDL.h"
# define WOLF3D_H

# define	WIN_SIZE_W		1600
# define	WIN_SIZE_H		900
# define	WIN_POS_X		SDL_WINDOWPOS_UNDEFINED
# define	WIN_POS_Y		SDL_WINDOWPOS_UNDEFINED
# define	WIN_TITLE		"Wolf 3D"
# define 	SIZE_RECT		20.0
# define	SOFTWARE		1

# define	FOV 			(3.14159 / 180.0 * 66.0)
# define	RAY_STEP		0.00125
# define	END_RAY			10.0
# define	PLAYER_ROTATE	3.14159 / 180
# define	PLAYER_MOVE		0.0125
# define	TIMEOUT_MILISEC	30

# define	FD_ERR			2
# define	NO_ERR			0
# define	SIZE_ERR		-1
# define	MEM_ERR			-2
# define	VERSION_ERR		-3
# define	SDL_ERR			-4
# define	MAP_ERR			-5
# define	PLY_ERR			-6

typedef double			numeric;

typedef enum			e_game_state
{
	G_QUIT = 0,
	G_PROCESS = 1,
	G_EDITOR = 2,
	G_PAUSE = 3,
	G_MENU = 4,
}						t_game_state;

typedef enum			e_move
{
	PM_NONE = 0,
	PM_FRONT = 1,
	PM_RIGHT = 2,
	PM_BACK = 3,
	PM_LEFT = 4
}						t_move;

typedef struct			s_font
{
	int					full_w;
	int					full_h;
	int					letter_w;
	int					letter_h;
	int					rows_count;
	int					cols_count;
	char				*array;
	unsigned int		*pixels;
	unsigned int		transparent_color;
}						t_font;

typedef struct			s_player
{
	numeric				pos_x;
	numeric				pos_y;
	numeric				watch_x;
	numeric				watch_y;
	int					prev_mouse_x;
	t_move				move;
}						t_player;

typedef struct			s_menu_button
{
	SDL_Rect			rect;
	t_game_state		state;
	char				*text;
}						t_menu_button;

typedef	struct			s_map {
	int					size_x;
	int					size_y;
	char				*array;
	int					startpos;
	int					endpos;
	int					version;
}						t_map;

typedef struct			s_ray
{
	double				dir_x;
	double				dir_y;
	double				dist_x;
	double				dist_y;
	double				delta_x;
	double				delta_y;
	double				perp_wall_dist;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
}						t_ray;

typedef struct			s_mouse {
	int 				x;
	int 				y;
	int 				button;
}						t_mouse;

typedef struct			s_game {
	SDL_Window			*wnd;
	SDL_Renderer		*rnd;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Rect			*rect;
	unsigned int		*pixels;
	int					pitch;
	t_game_state		state;
	t_player			*player;
	t_map				*level;
	int					is_software;
	numeric				fps;
	t_font				*font;
	t_mouse				*mouse;
	t_menu_button		*menu;
}						t_game;

t_map					*load_map_from_file(char const *filename);
void					render_game(t_game *game);
void					render_process_game(t_game *game);
int						render_menu_game(t_game *game);
void					process_game(t_game *game);
void					process_process_game(t_game *game);
void					process_menu_game(t_game *game);
int						create_renderer(t_game *game, int is_software);
int						create_window(t_game *game);
t_menu_button			*create_menu(t_game *game);
int						create_payer(t_game *game);
void					destroy_player(t_game *game);
int						destroy_window(t_game *game);
void					destroy_menu(t_game *game);
void					event_loop(t_game *game);
void					render_map(t_game *game);
int						render(t_game *game);
void					casting(t_game *game, t_ray *ray);
unsigned int			get_wall_color(t_ray *ray, t_game *game);
unsigned int			get_color_by_len(unsigned int max_bright,
	numeric length, numeric max_length);
SDL_Rect				create_rect(int x, int y, int w, int h);
void					fill_rect(unsigned int *pixels, SDL_Rect *view,
	SDL_Rect *rect, unsigned int color);
void					draw_line(unsigned int *pixels, SDL_Rect *view,
	SDL_Rect *line,	unsigned int color);


t_font					*load_font(char* filename, int rows_count,
	int cols_count);
int						set_array_font(t_font *font, char *array);
void					free_font(t_font *pfont);
void					print_str(t_game *game, SDL_Point p,
	t_font *font, char *str);
SDL_Point				set_to(int x, int y);

int						event_keyup_process(SDL_Event *event, t_game *game);
int						event_keyup_menu(SDL_Event *event, t_game *game);
int						event_mouse_process(SDL_Event *event, t_game *game);
int						event_mouse_menu(SDL_Event *event, t_game *game);
#endif //WOLF3D_H
