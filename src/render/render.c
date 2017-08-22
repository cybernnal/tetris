/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:50:22 by tbillard          #+#    #+#             */
/*   Updated: 2017/03/18 18:50:23 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void     draw_square(t_window *w, int x, int y, uint32_t color)
{
	int y2 = SQUARE_SIZE, x2 = 0;

	while (y2 >= 0)
	{
		while (x2 <= SQUARE_SIZE)
		{
			draw_pixel(x2 + x, y - y2, color, w);
			x2++;
		}
		y2--;
		x2 = 0;
	}
}

static void     save_time(t_env *e)
{
    e->current.last_move = clock();
}

static void     pop_piece(t_env *e)
{
	int r = rand() % 4;
	int p = rand() % 7;
	int x = (MAP_X / 2) - 2;
	int i = 0;

	ft_memset(&e->current, -1, sizeof(t_current));
    e->current.p = p;
    e->current.x = x;
    e->current.y = 0;
    e->current.pop = 42;
	while (i < r)
	{
		e->p[p] = e->p[p]->next;
		i++;
	}
    save_piece(e);
	for (int j = 0 ; j < 4 ; j++) {
		e->map[0][x + j] = e->p[p]->piece[0][j];
	}
    save_time(e);
}

static void         go_down(t_env *e)
{
	if (e->current.y < 4)
	{
		if (check_down(e) == 1)
		{
			ft_putendl("game over");
			exit(0);
		}
		delete_piece(e);
		e->current.y++;
		put_piece(e);
        save_time(e);
		return;
	}
    if (check_down(e) == 1)
    {
        e->current.down = -1;
        e->current.pop = -1;
        pop_piece(e);
        return;
    }
	delete_piece(e);
	e->current.y++;
	put_piece(e);
	if (check_down(e) == 1)
	{
		e->current.down = -1;
		e->current.pop = -1;
	}
    save_time(e);
}

static void         render_map(t_window *w, t_env *e)
{
	int i = 0, j = 0;

	while (i < MAP_Y)
	{
		while (j < MAP_X)
		{
			if (e->map[i][j] > 0)
			{
				draw_square(w, X0 + ((j) * (SQUARE_SIZE + SQUARE_SPACE)), Y0 + ((i + 1) * (SQUARE_SIZE + SQUARE_SPACE)), e->map[i][j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void         check_line(t_env *e)
{
    int off = 0;

    if (check_down(e) == 0)
        return;
    for (int i = MAP_Y - 1 ; i >= 0 ; i--)
    {
        int is_full = 0;

        for (int j = 0 ; j < MAP_X ; j++)
        {
            if (e->map[i][j] == 0)
            {
                is_full = -1;
                break ;
            }
        }
        if (is_full >= 0)
        {
            for (int j = 0 ; j < MAP_X ; j++)
                e->map[i][j] = 0;
            off++;
        }
        else
        {
            for (int j = 0 ; j < MAP_X ; j++)
                e->map[i + off][j] = e->map[i][j];
        }
    }
}

static void         render_other(t_window *w)
{
	int x0 = X0 - SQUARE_SPACE;
	int x1 = ((MAP_X + 2)* (SQUARE_SIZE + SQUARE_SPACE)) + SQUARE_SPACE * 4;
	int y0 = Y0 - SQUARE_SPACE;
	int y1 = (MAP_Y * (SQUARE_SIZE + SQUARE_SPACE)) + SQUARE_SPACE * 2;

	for (int i = y0; i <= y1 ; i++)
	{
		for (int j = x0; j <= x1 ; j++)
		{
			if (i == y0 || i == y1 || j == x0 || j == x1) {
				draw_pixel(j, i, 0x7F7F7F, w);
			}
//            if ((j - X0) % (SQUARE_SIZE + SQUARE_SPACE / 2) == 0)
//                draw_pixel(j + SQUARE_SPACE , i , 0x7F7F7F, w);
//			if ((i - y0) % SQUARE_SIZE == 0 || (j - x0) % SQUARE_SIZE == 0)
//				draw_pixel(j + SQUARE_SPACE , i - SQUARE_SPACE, 0x7F7F7F, w);
		}
	}
}

static void         render_tet(t_window *w, t_env *env)
{

    if (((float)clock() - (float)env->current.last_move) / (float)CLOCKS_PER_SEC >= env->duration || env->current.down != -1)
    {
        if (env->current.pop < 0)
            pop_piece(env);
        else
            go_down(env);
    }
    check_line(env);
    render_map(w, env);
    render_other(w);
//	printf("current: x: %d, y: %d, p: %d\n", env->current.x, env->current.y, env->current.p);
}

int					render(t_env *env)
{
	static t_window w;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
	bzero(w.img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
	while (SDL_PollEvent(&w.event))
		key_hook(w.event, env);
	render_tet(&w, env);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_X * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
	return (1);
}