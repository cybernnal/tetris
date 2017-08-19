/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:46:15 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:28:40 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"
#include <stdio.h>
#include "audio.h"

void    init_env(t_env *env)
{
    ft_bzero(env, sizeof(t_env));
	init_tet(env);
	ft_memset(&env->current, -1, sizeof(t_current));
}

int		main(int argc, char  **argv)
{
	t_env	env;

	int i = 0, j = 0, k = 0;
	if (argc < 1)
		ft_error("too few args");
    init_env(&env);
	srand((unsigned int)time(NULL));
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return 1;
	}
	initAudio();
	playMusic("../Tetris.wav", SDL_MIX_MAXVOLUME);
	   while (render(&env));
	return (0);
}
