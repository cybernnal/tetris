/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:16:40 by tbillard          #+#    #+#             */
/*   Updated: 2017/03/18 16:17:38 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"
#include "tetris.h"


static void  rotate(t_env *e, int p, int r)
{
    int i = 0, j = 0;

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
    }
}

static void delete_piece(t_env *e)
{
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

//    for (int i = e->current.i ; i >= 0 ; i--)
//    {
//        for (int j = 0; j < 4 ; j++)
//        {
//            if (e->current.comp_p[i][j] > 0)
//                e->map[e->current.y - (e->current.i - i)][e->current.x + i] = 0;
//        }
//    }
}


static void put_piece(t_env *e)
{
    for (int i = e->current.i ; i >= 0 ; i--)
    {
        for (int j = 0; j < 4 ; j++)
        {
            if (e->current.comp_p[i][j] > 0)
                e->map[e->current.y - (e->current.i - i)][e->current.x + i] = e->current.comp_p[i][j];
        }
    }
}

int ft_exit(t_env *e)
{
    exit (0);
}

int ft_mute(t_env *e)
{
    if (e->mute == 0)
    {
        pauseAudio();
        e->mute = 1;
    }
    else
    {
        unpauseAudio();
        e->mute = 0;
    }
    return (0);
}

int ft_rotate(t_env *env)
{
    delete_piece(env);
    env->current.rotate = (env->current.rotate + 1) % 4;
    rotate(env, env->current.p, env->current.rotate);
//    put_piece(env);
    return (1);
}

int ft_left(t_env *env)
{
    delete_piece(env);
    if (env->current.x > 0) // TODO not good
        env->current.x--;
//    put_piece(env);
    return (1);
}


int ft_right(t_env *env)
{
    delete_piece(env);
    if (env->current.x < MAP_X) // TODO not good
        env->current.x++;
//    put_piece(env);
    return (1);
}

int ft_down(t_env *env)
{
    env->current.down = 1;
    return (0);
}

void		ft_tab_ft_init_1(int (**tab_ft)(t_env*))
{
	tab_ft[SDLK_ESCAPE] = &ft_exit;
    tab_ft[SDLK_m] = &ft_mute;
    tab_ft[SDLK_s] = &ft_down;
    tab_ft[SDLK_w] = &ft_rotate;
    tab_ft[SDLK_a] = &ft_left;
    tab_ft[SDLK_d] = &ft_right;
}

int		nil(t_env *env)
{
    return (0);
}
