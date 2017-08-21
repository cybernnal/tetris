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

static int check_right(t_env *env)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (env->current.comp_p[i][j] > 0 && (env->current.x + j + 1 >= MAP_X || (env->map[env->current.y - (3 - i)][env->current.x + j + 1] > 0 && (j + 1 > 3 || env->current.comp_p[i][j + 1] == 0))))
                return (1);
        }
    }
    return (0);
}

static int check_left(t_env *env)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (env->current.comp_p[i][j] > 0 && (env->current.x + j - 1 < 0 || (env->map[env->current.y - (3 - i)][env->current.x + j - 1] > 0 && (j - 1 < 0 || env->current.comp_p[i][j - 1] == 0))))
                return (1);
        }
    }
    return (0);
}

static int check_rleft(t_env *env, uint32_t piece[4][4])
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (piece[i][j] > 0 && (env->current.x + j < 0 || (env->map[env->current.y - (3 - i)][env->current.x + j] > 0 && (j < 0 || piece[i][j] == 0))))
                return (1);
        }
    }
    return (0);
}

static int check_rright(t_env *env, uint32_t piece[4][4])
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (piece[i][j] > 0 && (env->current.x + j >= MAP_X || (env->map[env->current.y - (3 - i)][env->current.x + j] > 0 && (j > 3 || piece[i][j] == 0))))
                return (1);
        }
    }
    return (0);
}

static int check_rotate(t_env *env) // TODO check botom for rotate, rotate or not
{
    t_piece *p = env->p[env->current.p]->next;
    int     x = env->current.x;
    int i = 0;

    while (i < 3)
    {
        if (check_rleft(env, p->piece) == 0) {
            break ;
        }
        i++;
        env->current.x++;
    }
    if (i == 3)
    {
        env->current.x = x;
        return (0);
    }
    while (i < 3)
    {
        if (check_rright(env, p->piece) == 0) {
            break ;
        }
        i++;
        env->current.x--;
    }
    if (i == 3)
    {
        env->current.x = x;
        return (0);
    }
    return (1);
}

int ft_rotate(t_env *env) // TODO fix rotation (if rotate next to the wall or other piece) conflict!!
{
    if (env->current.y < 3)
        return (0);

    delete_piece(env);
    if (check_rotate(env) == 1)
    {
        env->p[env->current.p] = env->p[env->current.p]->next;
        save_piece(env);
    }
    put_piece(env);
    return (1);
}

int ft_left(t_env *env)
{
    if (env->current.y < 3)
        return (0);
    if (check_left(env) == 1)
        return (0);
    delete_piece(env);
    env->current.x--;
    put_piece(env);
    if (check_down(env) == 0)
        env->current.pop = 0;
    return (1);
}

int ft_right(t_env *env)
{
    if (env->current.y < 3)
        return (0);
    if (check_right(env) == 1)
        return (0);
    delete_piece(env);
    env->current.x++;
    put_piece(env);
    if (check_down(env) == 0)
        env->current.pop = 0;
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
    tab_ft[SDLK_SPACE] = &ft_down;
}

int		nil(t_env *env)
{
    return (0);
}