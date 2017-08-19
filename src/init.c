#include "tetris.h"

static void init_texture_renderer(t_window *win, int w, int h)
{
	if (!(win->img_ptr = (Uint32 *)ft_memalloc(sizeof(Uint32) * w * h)))
		exit(EXIT_FAILURE);
	win->image = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}

void        init_window(t_window *window)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->window = SDL_CreateWindow("fdf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))
		exit(EXIT_FAILURE);
	if (!(window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED)))
		exit(EXIT_FAILURE);
	init_texture_renderer(window, WIN_X, WIN_Y);
}


void	init_tet(t_env *e)
{
	e->piece[0][0][0] = 1;
	e->piece[0][0][1] = 1;
	e->piece[0][0][2] = 1;
	e->piece[0][0][3] = 1;

	e->piece[1][0][0] = 1;
	e->piece[1][0][1] = 1;
	e->piece[1][1][0] = 1;
	e->piece[1][1][1] = 1;

	e->piece[2][0][0] = 1;
	e->piece[2][0][1] = 1;
	e->piece[2][0][2] = 1;
	e->piece[2][1][2] = 1;

	e->piece[3][0][0] = 1;
	e->piece[3][0][1] = 1;
	e->piece[3][0][2] = 1;
	e->piece[3][1][0] = 1;

	e->piece[4][0][0] = 1;
	e->piece[4][0][1] = 1;
	e->piece[4][0][2] = 1;
	e->piece[4][1][1] = 1;

	e->piece[5][0][1] = 1;
	e->piece[5][0][2] = 1;
	e->piece[5][1][0] = 1;
	e->piece[5][1][1] = 1;

	e->piece[6][0][0] = 1;
	e->piece[6][0][1] = 1;
	e->piece[6][1][1] = 1;
	e->piece[6][1][2] = 1;
}