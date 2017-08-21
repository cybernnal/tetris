/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:17:55 by tbillard          #+#    #+#             */
/*   Updated: 2017/03/18 16:19:19 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void		ft_tab_ft_init(int (**tab_ft)(t_env*))
{
	int i;

	i = 0;
	while (i < 150)
		tab_ft[i++] = &nil;
	ft_tab_ft_init_1(tab_ft);
}

int				key_hook(SDL_Event k, t_env *e)
{
	static int		(*t_hook[150])(t_env*) = {NULL};

	if (!t_hook[0]) {
		ft_tab_ft_init(t_hook);
	}
	if (k.key.type == SDL_KEYDOWN)
    {
        if (k.key.keysym.sym == SDLK_DOWN)
            t_hook[SDLK_s](e);
        else if (k.key.keysym.sym == SDLK_LEFT)
            t_hook[SDLK_a](e);
        else if (k.key.keysym.sym == SDLK_RIGHT)
            t_hook[SDLK_d](e);
        else if (k.key.keysym.sym == SDLK_UP)
            t_hook[SDLK_w](e);
        if (k.key.keysym.sym >= 150 || k.key.keysym.sym < 0)
            return (0);
        t_hook[k.key.keysym.sym](e);
    }
    return (0);
}
