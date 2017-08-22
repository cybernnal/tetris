//
// Created by tom billard on 21/08/2017.
//

#include "tetris.h"

void write_server(SOCKET sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}


int read_server(SOCKET sock, char *buffer)
{
    int n = 0;

    if((n = (int)recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }
    buffer[n] = 0;
    return n;
}