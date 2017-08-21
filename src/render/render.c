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

static void draw_square(t_window *w, int x, int y, uint32_t color)
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

void    save_time(t_env *e)
{
    e->current.last_move = clock();
}

void save_piece(t_env *e)
{
    for (int j = 0 ; j < 4 ; j++) {
        for (int k = 0; k < 4 ; k++)
        {
            e->current.comp_p[j][k] = e->p[e->current.p]->piece[j][k];
        }
    }
}

static void pop_piece(t_env *e)
{
	int r = rand() % 4;
//	r = 0;
	int p = rand() % 7;
//	p = 5;
	int x = (MAP_X / 2) - 2;
	int i = 0;



    printf("rotation: %d\n", r);
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

void delete_piece(t_env *e)
{
	for (int i = 0; i < 4; i++) {
		if (e->current.y + i < 3)
			continue;
		for (int j = 0; j < 4; j++)
		{
			if (e->current.comp_p[i][j] > 0)
				e->map[e->current.y - (3 - i)][e->current.x + j] = 0;
		}
	}
}

static void put_piece(t_env *e)
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (e->current.y + i < 3)
			continue;
		for (int j = 0 ; j < 4 ; j++)
		{
			if (e->current.comp_p[i][j] == 0)
				continue ;
			e->map[e->current.y - (3 - i)][e->current.x + j] = e->current.comp_p[i][j];
		}
	}
}

static int check_down(t_env *e)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        if (e->current.y + i < 3)
			continue;
        for (int j = 0 ; j < 4 ; j++)
        {
            if (e->current.comp_p[i][j] > 0 && (e->current.y - (3 - i) + 1 >= MAP_Y || (e->map[(e->current.y - (3 - i)) + 1][e->current.x + j] > 0 && (i + 1 > 3 || e->current.comp_p[i + 1][j] == 0))))
                return (1);
        }
    }
//
//    for (int i = 0; i < 4; i++) {
//		if (e->current.y + i < 3)
//			continue;
//
//		for (int j = 0; j < 4; j++)
//		{
//			if (e->current.comp_p[i][j] > 0 && (i == 3 || e->current.comp_p[i + 1][j] == 0) && e->map[(e->current.y - (3 - i)) + 1][e->current.x + j] > 0)
//            {
//                return (1);
//            }
//			if (e->current.y + 1 >= MAP_Y)
//				return (1);
//		}
//	}
	return (0);
}

static void go_down(t_env *e) // TODO add time
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



static void render_map(t_window *w, t_env *e)// TODO marche pas // peu etre que si
{
	int i = 0, j = 0;

	while (i < MAP_Y)
	{
		while (j < MAP_X)
		{
			if (e->map[i][j] > 0)
			{
				draw_square(w, X0 + ((j) * (SQUARE_SIZE + SQUARE_SPACE)), Y0 +  ((i + 1) * (SQUARE_SIZE + SQUARE_SPACE)), e->map[i][j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void render_other(t_window *w)
{
    int x0 = X0 - SQUARE_SPACE;
    int x1 = ((MAP_X + 3)  * (SQUARE_SIZE + SQUARE_SPACE))  + SQUARE_SPACE;
    int y0 = Y0 - SQUARE_SPACE;
    int y1 = (MAP_Y * (SQUARE_SIZE + SQUARE_SPACE)) + SQUARE_SPACE;

    for (int i = y0; i <= y1 ; i++)
    {
        for (int j = x0; j <= x1 ; j++)
        {
            if (i == y0 || i == y1 || i == y0 - 1 || i == y1 - 1 || j == x0 || j == x1 || j == x0 - 1 || j == x1 - 1) {
                draw_pixel(j, i, 0x7F7F7F, w);
            }
        }
    }
}

static void render_tet(t_window *w, t_env *env)
{

    if (((float)clock() - (float)env->current.last_move) / (float)CLOCKS_PER_SEC >= env->duration || env->current.down != -1)
    {
//        printf("clock: %lu, last: %lu, calc: %f, duration: %f\n", clock(), env->current.last_move, ((float)clock() - (float)env->current.last_move) / (float)CLOCKS_PER_SEC, env->duration);
        if (env->current.pop < 0)
            pop_piece(env);
        else
            go_down(env);
    }
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
