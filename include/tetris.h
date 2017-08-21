/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:40:53 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:13:54 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

# include "../libft/libft.h"
#include <errno.h>

//#include ""
#include "SDL.h"
//#include "sdl2.h"
#include <time.h>

#define WIN_X   900
#define WIN_Y   1050
#define MARGE   10
#define WIN_X1   WIN_X - MARGE
#define WIN_Y1   WIN_Y - MARGE

#define CONF_X0 (WIN_X - (WIN_X / 7))
#define CONF_YM  (WIN_Y / 4)
#define NB 20

# define L_C(X, x1, x2, y1, y2) ((int)(((X - x1) * (y2 - y1)) / (x2 - x1)) + y1)
# define L_CF(X, x1, x2, y1, y2) ((float)(((float)((X - x1) * (y2 - y1))) / (float)(x2 - x1)) + y1)


#define X0 100
#define Y0 5
#define MAP_X 10
#define MAP_Y 25

//#define SQUARE_SIZE (int)L_CF(1, 0, MAP_X, 0, WIN_X1)


#define SQUARE_SIZE 30
#define SQUARE_SPACE 5

typedef float         t_tet;


typedef struct 				s_coor
{
	int 					x;
	int 					y;
}							t_corr;

typedef struct                  s_window
{
    SDL_Window              *window;
    SDL_Event               event;
    SDL_Renderer            *renderer;
    SDL_Texture             *image;
    Uint32                  *img_ptr;
    int                     is_init;
}                           t_window;

typedef struct 				s_piece
{
	uint32_t 					piece[4][4];
	int 					n;
	struct s_piece			*next;
}							t_piece;

typedef struct      s_current
{
    uint32_t            comp_p[4][4];
    uint32_t        color;
    int             p;
	int             x;
    int             y;
    int             pop;
	int 			down;
    long unsigned int          last_move;

}                   t_current;

typedef struct		s_env
{
	struct s_piece		**p;
    uint32_t               map[MAP_Y][MAP_X];
    struct s_current    current;
	int 				mute;
    float               duration;
}			    		    t_env;

void			init_lst(t_env *e);
void    			init_env(t_env *env);
void               init_window(t_window *window);
int                render(t_env *env);
int					ft_error(char *str);
void delete_piece(t_env *e);
void    init_current(t_env *e);
void	init_tet(t_env *e);
int		key_hook(SDL_Event k, t_env *e);
void		ft_tab_ft_init_1(int (**tab_ft)(t_env*));
void save_piece(t_env *e);
void draw_pixel(int x, int y, Uint32 color, t_window *w);
int     nil(t_env *env);

#endif
