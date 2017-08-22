//
// Created by tom billard on 21/08/2017.
//

#include <tetris.h>
#include "tetris.h"

static int init_connection(void)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };

    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        close(sock);
        exit(errno);
    }

    if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }

    return sock;
}

static int read_client(SOCKET sock, char *buffer)
{
    int n = 0;

    if((n = (int)recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }

    buffer[n] = 0;

    return n;
}

static void remove_client(Client *clients, int to_remove, int *actual)
{
    /* we remove the client in the array */
    memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
    /* number client - 1 */
    (*actual)--;
}

static void write_client(SOCKET sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}

static void send_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server)
{
    int i = 0;
    char message[BUF_SIZE];
    message[0] = 0;
    for(i = 0; i < actual; i++)
    {
        /* we don't send message to the sender */
        if(sender.sock != clients[i].sock)
        {
            if(from_server == 0)
            {
                strncpy(message, sender.name, BUF_SIZE - 1);
                strncat(message, " is now connected.", sizeof message - strlen(message) - 1);
            }
            strncat(message, buffer, sizeof message - strlen(message) - 1);
            write_client(clients[i].sock, message);
        }
    }
}

static void send_message_to_all(Client *clients, int actual, const char *buffer)
{
    int i = 0;
    char message[BUF_SIZE];
    message[0] = 0;
    for(i = 0; i < actual; i++)
    {
        strcpy(message, buffer);
        write_client(clients[i].sock, message);
    }
}

static void send_message_to(Client clients, const char *buffer)
{
    char message[BUF_SIZE];

    message[0] = 0;
    strcpy(message, buffer);
    write_client(clients.sock, message);
}

static void clear_clients(Client *clients, int actual)
{
    int i = 0;
    for(i = 0; i < actual; i++)
    {
        closesocket(clients[i].sock);
    }
}

static void end_connection(int sock)
{
    closesocket(sock);
}

static void game_server(int max, int actual, SOCKET sock, Client clients[MAX_CLIENTS], fd_set rdfs)
{
    int i;
    char buffer[BUF_SIZE];
    char piece[3];
    piece[2] = 0;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    send_message_to_all(clients, actual, "start");
    while (1)
    {
        FD_ZERO(&rdfs);


        /* add the connection socket */
        FD_SET(sock, &rdfs);

        /* add socket of each client */
        for(i = 0; i < actual; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }
        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }
        if(FD_ISSET(sock, &rdfs))
            ft_putendl("new clien very bad");
        else
        {
            for(i = 0; i < actual; i++)
            {

                if(FD_ISSET(clients[i].sock, &rdfs))
                {
                    Client client = clients[i];
                    int c = read_client(clients[i].sock, buffer);
                    if(c == 0)
                    {
                        closesocket(clients[i].sock);
                        remove_client(clients, i, &actual);
                        strncpy(buffer, client.name, BUF_SIZE - 1);
                        strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                        send_message_to_all_clients(clients, client, actual, buffer, 1);
                    }
                    else
                    {
                        if (!ft_strcmp(buffer, "gmp"))
                        {
                            piece[0] = (char) ((rand() % 7) + 1);
                            piece[1] = (char) ((rand() % 4) + 1);
                            send_message_to(client, piece);
                        }
                    }
                    break;
                }
            }
        }
    }
}

void appserv(void)
{
    SOCKET sock = init_connection();
    char buffer[BUF_SIZE];
    int i;
    /* the index for the array */
    int actual = 0;
    int max = sock;
    int cli = 0;
    /* an array for all clients */
    Client clients[MAX_CLIENTS];

    fd_set rdfs;

    while(1)
    {
        FD_ZERO(&rdfs);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the connection socket */
        FD_SET(sock, &rdfs);

        /* add socket of each client */
        for(i = 0; i < actual; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        if(FD_ISSET(sock, &rdfs))
        {
            cli = 1;
            /* new client */
            SOCKADDR_IN csin = { 0 };
            size_t sinsize = sizeof csin;
            int csock = accept(sock, (SOCKADDR *)&csin, (socklen_t *)&sinsize);
            if(csock == SOCKET_ERROR)
            {
                perror("accept()");
                continue;
            }

            /* after connecting the client sends its name */
            if(read_client(csock, buffer) == -1)
            {
                /* disconnected */
                continue;
            }
            printf("new clien: %s, number: %d\n", buffer, actual);

            /* what is the new maximum fd ? */
            max = csock > max ? csock : max;
            FD_SET(csock, &rdfs);
            Client c = { csock };
            c.name = ft_strdup(buffer);
            clients[actual] = c;
            send_message_to_all(clients, actual, "");
            actual++;
        }
        /* something from standard input : i.e keyboard */
        else if(FD_ISSET(STDIN_FILENO, &rdfs) && cli == 1)
        {
            //TODO input on server if == start start the game
            i = (int)read(STDIN_FILENO, buffer, BUF_SIZE);
            buffer[i - 1] = 0;
            if (!strcmp("start", buffer))
            {
                printf("Start the game\n"); // TODO start the game here
                game_server(max, actual, sock, clients, rdfs);
                clear_clients(clients, actual);
                end_connection(sock);
            }
            else if (!strcmp("quit", buffer))
            {
                printf("Quiting game.\n");
                break ;
            }
            else if (!strcmp("print", buffer))
            {
                for(i = 0; i < actual; i++)
                {
                    printf("%s\n", clients[i].name);
                }
                continue;
            }
            else
            {
                printf("please if all player are present type 'start' and enter for start the game: %s\n", buffer);
                continue;
            }
        }
        /*else
        {
            for(i = 0; i < actual; i++)
            {

                if(FD_ISSET(clients[i].sock, &rdfs))
                {
                    Client client = clients[i];
                    int c = read_client(clients[i].sock, buffer);

                    if(c == 0)
                    {
                        closesocket(clients[i].sock);
                        remove_client(clients, i, &actual);
                        strncpy(buffer, client.name, BUF_SIZE - 1);
                        strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                        send_message_to_all_clients(clients, client, actual, buffer, 1);
                    }
                    else
                    {
                        send_message_to_all_clients(clients, client, actual, buffer, 0);
                    }
                    break;
                }
            }
        }*/
    }
    clear_clients(clients, actual);
    end_connection(sock);
}