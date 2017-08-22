//
// Created by tom billard on 21/08/2017.
//
#include "tetris.h"

static int init_connection(const char *address)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    struct hostent *hostinfo;

    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    hostinfo = gethostbyname(address);
    if (hostinfo == NULL)
    {
        fprintf (stderr, "Unknown host %s.\n", address);
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }

    return sock;
}

static void end_connection(int sock)
{
    closesocket(sock);
}


void app_client(const char *address, const char *name, SOCKET sock)
{
//    SOCKET sock = init_connection(address);
    char buffer[BUF_SIZE];

    fd_set rdfs;

    /* send our name */
//    write_server(sock, name);

    while(1)
    {
        FD_ZERO(&rdfs);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the socket */
        FD_SET(sock, &rdfs);

        if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        /* something from standard input : i.e keyboard */
        if(FD_ISSET(STDIN_FILENO, &rdfs))
        {
            fgets(buffer, BUF_SIZE - 1, stdin);
            {
                char *p = NULL;
                p = strstr(buffer, "\n");
                if(p != NULL)
                {
                    *p = 0;
                }
                else
                {
                    /* fclean */
                    buffer[BUF_SIZE - 1] = 0;
                }
            }
            write_server(sock, buffer);
        }
        else if(FD_ISSET(sock, &rdfs))
        {
            int n = read_server(sock, buffer);
            /* server down */
            if(n == 0)
            {
                printf("Server disconnected !\n");
                break;
            }
            puts(buffer);
        }
    }

    end_connection(sock);
}

int         wait_start(SOCKET sock)
{
    char buffer[BUF_SIZE];
    fd_set rdfs;

    FD_ZERO(&rdfs);

    /* add the socket */
    FD_SET(sock, &rdfs);

    if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1) {
        perror("select()");
        exit(errno);
    }
    if (FD_ISSET(STDIN_FILENO, &rdfs));
    else if (FD_ISSET(sock, &rdfs))
    {
        int n = read_server(sock, buffer);
        /* server down */
        if (n == 0) {
            printf("Server disconnected !\n");
            return (-1);
        }
        if (ft_strcmp(buffer, "start"))
            printf("buf: |%s|\n", buffer);
        else
            return (1);
    }
    return (0);
}

SOCKET        connect_server(const char *address, const char *name)
{
    SOCKET sock = init_connection(address);

    write_server(sock, name);
    return (sock);
}