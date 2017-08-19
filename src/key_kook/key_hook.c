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
	if (k.key.keysym.sym >= 150 || k.key.keysym.sym < 0)
		return (0);
	if (k.key.type == SDL_KEYDOWN) {
//		printf("key: %d\n", k.key.keysym.sym);
		t_hook[k.key.keysym.sym](e);
	}
    return (0);
}
