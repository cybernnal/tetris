//
// Created by tom billard on 21/08/2017.
//



#include "tetris.h"

void            save_piece(t_env *e)
{
    for (int j = 0 ; j < 4 ; j++) {
        for (int k = 0; k < 4 ; k++)
        {
            e->current.comp_p[j][k] = e->p[e->current.p]->piece[j][k];
        }
    }
}

void            delete_piece(t_env *e)
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

int             check_down(t_env *e)
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
    return (0);
}

void             put_piece(t_env *e)
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

int             check_right(t_env *env)
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

int             check_left(t_env *env)
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

int             check_rleft(t_env *env, uint32_t piece[4][4])
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

int             check_rright(t_env *env, uint32_t piece[4][4])
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