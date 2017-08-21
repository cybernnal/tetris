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

int             ft_exit(t_env *e)
{
    exit (0);
}

int             ft_mute(t_env *e)
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

static int      check_rotate(t_env *env) // TODO check botom for rotate, rotate or not
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

int         ft_rotate(t_env *env) // TODO fix rotation (if rotate next to the wall or other piece) conflict!!
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

int         ft_left(t_env *env)
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

int         ft_right(t_env *env)
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

int         ft_down(t_env *env)
{
    env->current.down = 1;
    return (0);
}

int         ft_change_music(t_env *env)
{
    endAudio();
    initAudio();
   if (env->music == 0)
       playMusic("../resource/Tetris_ah.wav", SDL_MIX_MAXVOLUME);
   if (env->music == 1)
        playMusic("../resource/Tetris.wav", SDL_MIX_MAXVOLUME);
    env->music = !env->music;
    return (1);
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
    tab_ft[SDLK_i] = &ft_change_music;
}

int		nil(t_env *env)
{
    return (0);
}
