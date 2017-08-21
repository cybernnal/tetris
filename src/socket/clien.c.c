//
// Created by tom billard on 21/08/2017.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> /* gethostbyname */
#include "tetris.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)


#define PORT	 1977

#define BUF_SIZE 1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

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

static void write_server(SOCKET sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}

static void end_connection(int sock)
{
    closesocket(sock);
}

static int read_server(SOCKET sock, char *buffer)
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

static void app(const char *address, const char *name)
{
    SOCKET sock = init_connection(address);
    char buffer[BUF_SIZE];

    fd_set rdfs;

    /* send our name */
    write_server(sock, name);

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

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage : %s [address] [pseudo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    app(argv[1], argv[2]);

    return EXIT_SUCCESS;
}