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

void    init_env(t_env *env)
{
    ft_bzero(env, sizeof(t_env));
    init_lst(env);
    env->duration = 0.5;
	ft_memset(&env->current, -1, sizeof(t_current));
    env->current.last_move = 0;
}

int		main(int argc, char  **argv)
{
	t_env	env;

	if (argc < 1)
		ft_error("too few args");
    init_env(&env);
	srand((unsigned int)time(NULL));
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return 1;
	}
	initAudio();
	playMusic("../resource/Tetris.wav", SDL_MIX_MAXVOLUME); // TODO uncomment
	   while (render(&env));
	return (0);
}
