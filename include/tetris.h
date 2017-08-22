/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:40:53 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:13:54 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

#include "../libft/libft.h"
#include <errno.h>
#include "audio.h"
#include <time.h>
#include "SDL.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define WIN_X   900
#define WIN_Y   1050
#define MARGE   10

#include <SDL_ttf.h>
#define WIN_X1   WIN_X - MARGE
#define WIN_Y1   WIN_Y - MARGE

# define L_CF(X, x1, x2, y1, y2) ((float)(((float)((X - x1) * (y2 - y1))) / (float)(x2 - x1)) + y1)


#define X0 100
#define Y0 5

#define MAP_X 10
#define MAP_Y 25

#define SQUARE_SIZE 36
#define SQUARE_SPACE 5

#define BUF_SIZE	1024

#define PSEDO_LEN   11

#define PORT	 1977

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define MAX_CLIENTS 	7

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct
{
    SOCKET sock;
    char *name;
}Client;

uint32_t     color[7] = {0xFF0000, 0x00FFFF, 0xED7F10, 0xFFFF00, 0x00FF00, 0xAFAFAF, 0x0000FF};

typedef struct          s_window
{
    SDL_Window          *window;
    SDL_Event           event;
    SDL_Renderer        *renderer;
    SDL_Texture         *image;
    Uint32              *img_ptr;
    int                 is_init;
}                       t_window;

typedef struct 			s_piece
{
	uint32_t 			piece[4][4];
	int 				n;
	struct s_piece		*next;
}					    t_piece;

typedef struct          s_current
{
    uint32_t            comp_p[4][4];
    int                 p;
	int                 x;
    int                 y;
    int                 pop;
	int 			    down;
    long unsigned int   last_move;

}                       t_current;

typedef struct		    s_env
{
    int                 pid;
    char                *address;
    int                 is_client;
    char                *psedo;
	struct s_piece		**p;
    uint32_t            map[MAP_Y][MAP_X];
    struct s_current    current;
	int 				mute;
    float               duration;
    Client              client;
}			    		t_env;

void			        init_lst(t_env *e);
void    			    init_env(t_env *env);
void                    init_window(t_window *window);
int                     render(t_env *env);
int					    ft_error(char *str);
void                    delete_piece(t_env *e);
int                     check_down(t_env *e);
int             		key_hook(SDL_Event k, t_env *e);
void		            ft_tab_ft_init_1(int (**tab_ft)(t_env*));
void                    save_piece(t_env *e);
void                    draw_pixel(int x, int y, Uint32 color, t_window *w);
int                     nil(t_env *env);
void                    put_piece(t_env *e);
int                     check_right(t_env *env);
int                     check_left(t_env *env);
int                     check_rleft(t_env *env, uint32_t piece[4][4]);
int                     check_rright(t_env *env, uint32_t piece[4][4]);

void                    appserv(void);
void                    app_client(const char *address, const char *name, SOCKET sock);
SOCKET                  connect_server(const char *address, const char *name);
int                     wait_start(SOCKET sock);
void                    write_server(SOCKET sock, const char *buffer);
int                     read_server(SOCKET sock, char *buffer);

#endif
