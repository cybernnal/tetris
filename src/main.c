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

#include <signal.h>
#include <tetris.h>
#include "tetris.h"

void    init_env(t_env *env)
{
    ft_bzero(env, sizeof(t_env));
    init_lst(env);
    env->duration = 0.1;
	ft_memset(&env->current, -1, sizeof(t_current));
    env->current.last_move = 0;
	env->psedo = (char*)ft_memalloc(sizeof(char) * PSEDO_LEN);
    env->address = (char*)ft_memalloc(sizeof(char) * BUF_SIZE);
}

t_env   *sig_env(t_env *env, int i)
{
    static t_env *e;

    if (i == 1)
        e = env;
    return (e);
}

void ft_atexit(void) {
    t_env *e = sig_env(NULL, 0);

    if (e->pid > 0)
        kill(e->pid, 15);
}

int		main(int argc, char  **argv)
{
	t_env	env;
	int		pid = -1;
    int     ret;

    sysconf(_SC_ATEXIT_MAX);
    atexit(ft_atexit);
	if (argc < 1) {
		ft_error("too few args");
	}
    srand((unsigned int)time(NULL));
    sig_env(&env, 1);
	init_env(&env);
	if (argc > 1) {
		if (!ft_strcmp(argv[1], "-s")) {
			pid = fork();
            env.pid = pid;
			if (pid < 0) {
				ft_error("Fork error");
			} else if (pid == 0) {
				appserv();
				return (0);
			}
		}
		if (pid > 0 || !ft_strcmp(argv[1], "-c")) {
			printf("Please enter your psedo (max 10 char): ");
			scanf("%s", env.psedo);
			env.is_client = 1;
//            env.client.name = env.psedo;
//            if (pid > 0)
                ft_strcpy(env.address, "127.0.0.1");
//            else TODO uncomment
//            {
//                printf("Please enter the server's hostname or ip: ");
//                scanf("%s", env.address);
//            }
            env.client.sock = connect_server(env.address, env.psedo);
            usleep(10000);
            while (!(ret = wait_start(env.client.sock)));
            if (ret < 0)
                exit(0);
            ft_putendl("reggae!!!");
            env.is_client = 1;
//            while (1);
		}
//		if (pid > 0)
//			kill(pid, 15);
	}
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return 1;
	}
	initAudio();
	playMusic("resource/Tetris.wav", SDL_MIX_MAXVOLUME); // TODO uncomment
	   while (render(&env));
	return (0);
}
