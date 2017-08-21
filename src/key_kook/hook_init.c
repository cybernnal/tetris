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

static int check_right(t_env *e)
{
    for (int j = 3 ; j >= 0 ; j--)
    {
        for (int i = 0; i < 4; i++)
        {
            if (e->current.comp_p[i][j] > 0)
                return (j);

        }
    }
    ft_putendl("error in check right");
    return (0);
}


static int check_left(t_env *e)
{
    for (int j = 0 ; j < 4 ; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (e->current.comp_p[i][j] > 0)
                return (j);

        }
    }
    ft_putendl("error in check left");
    return (0);
}

int ft_rotate(t_env *env) // TODO fix rotation (if rotate next to the wall or other piece) conflict!!
{
    if (env->current.y < 3)
        return (0);
    delete_piece(env);
    env->p[env->current.p] = env->p[env->current.p]->next;
    save_piece(env);
    put_piece(env);
    return (1);
}

int ft_left(t_env *env)
{
    if (env->current.y < 3)
        return (0);
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (env->current.comp_p[i][j] > 0 && (env->current.x + j - 1 < 0 || (env->map[env->current.y - (3 - i)][env->current.x + j - 1] > 0 && (j - 1 < 0 || env->current.comp_p[i][j - 1] == 0))))
                return (0);
        }
    }
    delete_piece(env);
    env->current.x--;
    put_piece(env);
    return (1);
}


int ft_right(t_env *env)
{
    if (env->current.y < 3)
        return (0);
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (env->current.comp_p[i][j] > 0 && (env->current.x + j + 1 >= MAP_X || (env->map[env->current.y - (3 - i)][env->current.x + j + 1] > 0 && (j + 1 > 3 || env->current.comp_p[i][j + 1] == 0))))
                return (0);
        }
    }

    delete_piece(env);
//    if (env->current.x + 4 < MAP_X) // TODO not good
    env->current.x++;
    put_piece(env);
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
