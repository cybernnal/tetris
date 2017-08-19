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

static void render_piece(t_window *w, t_env *env, int x, int y, int piece, uint32_t color)
{
	int y2 = 3, x2 = 0;

	while (y2 >= 0)
	{
		while (x2 < 4)
		{
			if (env->piece[piece][y2][x2])
				draw_square(w, x + (x2 * (SQUARE_SIZE + SQUARE_SPACE)), y - (y2 * (SQUARE_SIZE + SQUARE_SPACE)),color);
			x2++;
		}
		y2--;
		x2 = 0;
	}
}

static int get_p_y(char piece[4][4])
{
	int i = 3, j = 0, k = 0;

	while (i >= 0)
	{
		while (j < 4)
		{
			if (piece[i][j] != 0)
				k = 1;
			j++;
		}
		if (k == 1)
			break ;
		j = 0;
		i--;
	}
	return (i);
}

static char  *get_value(t_env *e, int p, int r)
{
	int i = 0, j = 0, k = 0;
	char *piece;

	piece = (char*)ft_memalloc(sizeof(char) * 4);
	if (r == 0)
	{
		while (i < 4)
		{
			while (j < 4)
			{
				e->current.comp_p[i][j] = e->piece[p][i][j];
				j++;
			}
			j = 0;
			i++;
		}
		i = get_p_y(e->piece[p]);
		j = 0;
		while (j < 4)
			piece[j] = e->piece[p][i][j++];
		e->current.i = i;
		return (piece);
	}
	if (r == 1)
	{
		while (i < 4)
		{
			while (j < 4)
			{
				e->current.comp_p[j][3 - i] = e->piece[p][i][j];
				j++;
			}
			j = 0;
			i++;
		}
		i = get_p_y(e->current.comp_p);
		j = 0;
		while (j < 4)
			piece[j] = e->current.comp_p[i][j++];
		e->current.i = i;
		return (piece);
	}
	if (r == 2)
	{
		while (i < 4)
		{
			while (j < 4)
			{
				e->current.comp_p[3 - j][3 - i] = e->piece[p][i][j];
				j++;
			}
			j = 0;
			i++;
		}
		i = get_p_y(e->current.comp_p);
		j = 0;
		while (j < 4)
			piece[j] = e->current.comp_p[i][j++];
		e->current.i = i;
		return (piece);
	}
	if (r == 3)
	{
		while (i < 4)
		{
			while (j < 4)
			{
				e->current.comp_p[3 - j][i] = e->piece[p][i][j];
				j++;
			}
			j = 0;
			i++;
		}
		i = get_p_y(e->current.comp_p);
		j = 0;
		while (j < 4)
			piece[j] = e->current.comp_p[i][j++];
		e->current.i = i;
		return (piece);
	}
	return (NULL);
}

static void pop_piece(t_env *e)
{
	int r = rand() % 4;
//	r = 0;
	int p = rand() % 7;
//	p = 5;
	int x = (MAP_X / 2) - 2;
	char	*piece;

	ft_memset(&e->current, -1, sizeof(t_current));
	piece = get_value(e, p, r);
	for (int i = 0 ; i < 4 ; i++) {
		e->map[0][x + i] = piece[i];
	}
	e->current.piece = piece;
	e->current.p = p;
	e->current.rotate = r;
	e->current.x = x;
	e->current.y = 0;
	e->current.pop = 42;
}

static void go_down(t_env *e) // TODO add time
{
	if (e->current.y < e->current.i) //TODO  si ligne vide a i = 0 || i = 1 = pas passer dans condition
	{
		e->current.y++;
		for (int i = 0 ; i < 4 ; i++)
		{
			if (e->map[e->current.y][e->current.x + i] == 1 && e->map[e->current.y + 1][e->current.x + i] == 1)
			{
				ft_putendl("game over"); // TODO real game over
				exit(0);
			}
		}
		for (int i = e->current.i ; i >= 0 ; i--)
		{
			if (e->current.y - (e->current.i - i) < 0)
				continue ;
			for (int j = 0 ; j < 4 ; j++) // TODO piece pas sortit 4 c'est trop ||| 4 - j
			{
				if ((e->current.y - (e->current.i - i)) - 1 > 0)
					e->map[(e->current.y - (e->current.i - i)) - 1][e->current.x + j] = 0;
				e->map[e->current.y - (e->current.i - i)][e->current.x + j] = e->current.comp_p[i][j];
			}
		}
		return;
	}

	for (int i = e->current.i ; i >= 0 ; i--)
	{
		if (e->current.y - (e->current.i - i) < 0)
			continue ;
		for (int j = 0 ; j < 4 ; j++) // TODO piece pas sortit 4 c'est trop ||| 4 - j
		{
			if (e->current.comp_p[i][j] > 0)
				e->map[(e->current.y - (e->current.i - i))][e->current.x + j] = 0;
		}
	}


	e->current.y++;
	for (int i = e->current.i ; i >= 0 ; i--)
	{
		if (e->current.y - (e->current.i - i) < 0)
			continue ;
		for (int j = 0 ; j < 4 ; j++) // TODO piece pas sortit 4 c'est trop ||| 4 - j
		{
			if (e->current.comp_p[i][j] == 0)
				continue ;
			e->map[e->current.y - (e->current.i - i)][e->current.x + j] = e->current.comp_p[i][j];
			if ((e->current.y + 1 >= MAP_Y || ((i == e->current.i || e->current.comp_p[i + 1][j] == 0) && e->map[(e->current.y - (e->current.i - i)) + 1][e->current.x + j] == 1)))
			{
				e->current.down = -1;
				e->current.pop = -1;
			}
		}
	}
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
				draw_square(w, X0 + ((j + 1) * (SQUARE_SIZE + SQUARE_SPACE)), Y0 +  ((i + 1) * (SQUARE_SIZE + SQUARE_SPACE)), 0xff4444);
			}
				//draw_square(w, (int)5  + ((j + 1) * (SQUARE_SIZE + SQUARE_SPACE)), (int)(L_CF(i, 0, MAP_Y, 0, WIN_Y1) + ((i + 1) * (SQUARE_SIZE + SQUARE_SPACE))), 0xff4444);
			j++;
		}
		j = 0;
		i++;
	}
}

static void render_tet(t_window *w, t_env *env)
{

	uint32_t color = 0xff4444;
	int y = WIN_Y1, x = MARGE;
	int k = 0;

	if (env->current.pop < 0)
		pop_piece(env);
	else
		go_down(env);
	render_map(w, env);
	int i = 0, j = 0;

//	while (i < MAP_Y)
//	{
//		while (j < MAP_X)
//		{
//			ft_putnbr(env->map[i][j]);
//			ft_putstr(" ");
//			j++;
//		}
//		j = 0;
//		i++;
//		ft_putendl("");
//	}
	printf("current: x: %d, y: %d, i: %d, p: %d , r: %d\n", env->current.x, env->current.y, env->current.i, env->current.p, env->current.rotate);
//	exit(0);
//	while (k < 7)
//	{
//		render_piece(w, env, x, y, k, color);
//
//		k++;
//		y -= (4 * (SQUARE_SPACE + SQUARE_SIZE)) + SQUARE_SPACE;
//	}
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
	if (env->current.down == -1)
		sleep(1);
	return (1);
}
