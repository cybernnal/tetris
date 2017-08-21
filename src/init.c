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
	if (!(window->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))
		exit(EXIT_FAILURE);
	if (!(window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED)))
		exit(EXIT_FAILURE);
	init_texture_renderer(window, WIN_X, WIN_Y);
}

void	    init_lst(t_env *e)
{
	t_piece **piece = (t_piece**)ft_memalloc(sizeof(t_piece*) * 7);
	t_piece *tmp;

	piece[0] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[0]->piece[1][0] = 0xFF0000; // 0000
	piece[0]->piece[1][1] = 0xFF0000; // 1111
	piece[0]->piece[1][2] = 0xFF0000; // 0000
	piece[0]->piece[1][3] = 0xFF0000; // 0000

	tmp = piece[0];
	piece[0]->n = 0;
	piece[0]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[0] = piece[0]->next;
	piece[0]->n = 1;

	piece[0]->piece[0][2] = 0xFF0000; // 0010
	piece[0]->piece[1][2] = 0xFF0000; // 0010
	piece[0]->piece[2][2] = 0xFF0000; // 0010
	piece[0]->piece[3][2] = 0xFF0000; // 0010

	piece[0]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[0] = piece[0]->next;
	piece[0]->n = 2;

	piece[0]->piece[2][0] = 0xFF0000; // 0000
	piece[0]->piece[2][1] = 0xFF0000; // 0000
	piece[0]->piece[2][2] = 0xFF0000; // 1111
	piece[0]->piece[2][3] = 0xFF0000; // 0000

	piece[0]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[0] = piece[0]->next;
	piece[0]->n = 3;
	piece[0]->next = tmp;

	piece[0]->piece[0][1] = 0xFF0000; // 0100
	piece[0]->piece[1][1] = 0xFF0000; // 0100
	piece[0]->piece[2][1] = 0xFF0000; // 0100
	piece[0]->piece[3][1] = 0xFF0000; // 0100

	piece[0] = piece[0]->next;




	piece[1] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[1]->piece[1][1] = 0x00FFFF; // 0000
	piece[1]->piece[1][2] = 0x00FFFF; // 0110
	piece[1]->piece[2][1] = 0x00FFFF; // 0110
	piece[1]->piece[2][2] = 0x00FFFF; // 0000

	piece[1]->next = piece[1];
	piece[1]->n = 0;




	piece[2] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[2]->piece[0][0] = 0xED7F10; // 1000
	piece[2]->piece[1][0] = 0xED7F10; // 1110
	piece[2]->piece[1][1] = 0xED7F10; // 0000
	piece[2]->piece[1][2] = 0xED7F10; // 0000

	tmp = piece[2];
	piece[2]->n = 0;
	piece[2]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[2] = piece[2]->next;
	piece[2]->n = 1;

	piece[2]->piece[0][1] = 0xED7F10; // 0110
	piece[2]->piece[0][2] = 0xED7F10; // 0100
	piece[2]->piece[1][1] = 0xED7F10; // 0100
	piece[2]->piece[2][1] = 0xED7F10; // 0000

	piece[2]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[2] = piece[2]->next;
	piece[2]->n = 2;

	piece[2]->piece[1][0] = 0xED7F10; // 0000
	piece[2]->piece[1][1] = 0xED7F10; // 1110
	piece[2]->piece[1][2] = 0xED7F10; // 0010
	piece[2]->piece[2][2] = 0xED7F10; // 0000

	piece[2]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[2] = piece[2]->next;
	piece[2]->n = 3;
	piece[2]->next = tmp;

	piece[2]->piece[0][1] = 0xED7F10; // 0100
	piece[2]->piece[1][1] = 0xED7F10; // 0100
	piece[2]->piece[2][0] = 0xED7F10; // 1100
	piece[2]->piece[2][1] = 0xED7F10; // 0000

	piece[2] = piece[2]->next;




	piece[3] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[3]->piece[0][2] = 0xFFFF00; // 0010
	piece[3]->piece[1][0] = 0xFFFF00; // 1110
	piece[3]->piece[1][1] = 0xFFFF00; // 0000
	piece[3]->piece[1][2] = 0xFFFF00; // 0000

	tmp = piece[3];
	piece[3]->n = 0;
	piece[3]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[3] = piece[3]->next;
	piece[3]->n = 1;

	piece[3]->piece[0][1] = 0xFFFF00; // 0100
	piece[3]->piece[1][1] = 0xFFFF00; // 0100
	piece[3]->piece[2][1] = 0xFFFF00; // 0110
	piece[3]->piece[2][2] = 0xFFFF00; // 0000

	piece[3]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[3] = piece[3]->next;
	piece[3]->n = 2;

	piece[3]->piece[1][0] = 0xFFFF00; // 0000
	piece[3]->piece[1][1] = 0xFFFF00; // 1110
	piece[3]->piece[1][2] = 0xFFFF00; // 1000
	piece[3]->piece[2][0] = 0xFFFF00; // 0000

	piece[3]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[3] = piece[3]->next;
	piece[3]->n = 3;
	piece[3]->next = tmp;

	piece[3]->piece[0][0] = 0xFFFF00; // 1100
	piece[3]->piece[0][1] = 0xFFFF00; // 0100
	piece[3]->piece[1][1] = 0xFFFF00; // 0100
	piece[3]->piece[2][1] = 0xFFFF00; // 0000

	piece[3] = piece[3]->next;




	piece[4] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[4]->piece[0][1] = 0x00FF00; // 0110
	piece[4]->piece[0][2] = 0x00FF00; // 1100
	piece[4]->piece[1][0] = 0x00FF00; // 0000
	piece[4]->piece[1][1] = 0x00FF00; // 0000

	tmp = piece[4];
	piece[4]->n = 0;
	piece[4]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[4] = piece[4]->next;
	piece[4]->n = 1;

	piece[4]->piece[0][1] = 0x00FF00; // 0100
	piece[4]->piece[1][1] = 0x00FF00; // 0110
	piece[4]->piece[1][2] = 0x00FF00; // 0010
	piece[4]->piece[2][2] = 0x00FF00; // 0000

	piece[4]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[4] = piece[4]->next;
	piece[4]->n = 2;

	piece[4]->piece[1][1] = 0x00FF00; // 0000
	piece[4]->piece[1][2] = 0x00FF00; // 0110
	piece[4]->piece[2][0] = 0x00FF00; // 1100
	piece[4]->piece[2][1] = 0x00FF00; // 0000

	piece[4]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[4] = piece[4]->next;
	piece[4]->n = 3;
	piece[4]->next = tmp;

	piece[4]->piece[0][0] = 0x00FF00; // 1000
	piece[4]->piece[1][0] = 0x00FF00; // 1100
	piece[4]->piece[1][1] = 0x00FF00; // 0100
	piece[4]->piece[2][1] = 0x00FF00; // 0000

	piece[4] = piece[4]->next;




	piece[5] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[5]->piece[0][1] = 0xAFAFAF; // 0100
	piece[5]->piece[1][0] = 0xAFAFAF; // 1110
	piece[5]->piece[1][1] = 0xAFAFAF; // 0000
	piece[5]->piece[1][2] = 0xAFAFAF; // 0000

	tmp = piece[5];
	piece[5]->n = 0;
	piece[5]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[5] = piece[5]->next;
	piece[5]->n = 1;

	piece[5]->piece[0][1] = 0xAFAFAF; // 0100
	piece[5]->piece[1][1] = 0xAFAFAF; // 0110
	piece[5]->piece[1][2] = 0xAFAFAF; // 0100
	piece[5]->piece[2][1] = 0xAFAFAF; // 0000

	piece[5]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[5] = piece[5]->next;
	piece[5]->n = 2;

	piece[5]->piece[1][0] = 0xAFAFAF; // 0000
	piece[5]->piece[1][1] = 0xAFAFAF; // 1110
	piece[5]->piece[1][2] = 0xAFAFAF; // 0100
	piece[5]->piece[2][1] = 0xAFAFAF; // 0000

	piece[5]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[5] = piece[5]->next;
	piece[5]->n = 3;
	piece[5]->next = tmp;

	piece[5]->piece[0][1] = 0xAFAFAF; // 0100
	piece[5]->piece[1][0] = 0xAFAFAF; // 1100
	piece[5]->piece[1][1] = 0xAFAFAF; // 0100
	piece[5]->piece[2][1] = 0xAFAFAF; // 0000

	piece[5] = piece[5]->next;




	piece[6] = (t_piece*)ft_memalloc(sizeof(t_piece));

	piece[6]->piece[0][0] = 0x0000FF; // 1100
	piece[6]->piece[0][1] = 0x0000FF; // 0110
	piece[6]->piece[1][1] = 0x0000FF; // 0000
	piece[6]->piece[1][2] = 0x0000FF; // 0000

	tmp = piece[6];
	piece[6]->n = 0;
	piece[6]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[6] = piece[6]->next;
	piece[6]->n = 1;

	piece[6]->piece[0][2] = 0x0000FF; // 0010
	piece[6]->piece[1][1] = 0x0000FF; // 0110
	piece[6]->piece[1][2] = 0x0000FF; // 0100
	piece[6]->piece[2][1] = 0x0000FF; // 0000

	piece[6]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[6] = piece[6]->next;
	piece[6]->n = 2;

	piece[6]->piece[1][0] = 0x0000FF; // 0000
	piece[6]->piece[1][1] = 0x0000FF; // 1100
	piece[6]->piece[2][1] = 0x0000FF; // 0110
	piece[6]->piece[2][2] = 0x0000FF; // 0000

	piece[6]->next = (t_piece*)ft_memalloc(sizeof(t_piece));
	piece[6] = piece[6]->next;
	piece[6]->n = 3;
	piece[6]->next = tmp;

	piece[6]->piece[0][1] = 0x0000FF; // 0100
	piece[6]->piece[1][0] = 0x0000FF; // 1100
	piece[6]->piece[1][1] = 0x0000FF; // 1000
	piece[6]->piece[2][0] = 0x0000FF; // 0000

	piece[6] = piece[6]->next;

	e->p = piece;
}