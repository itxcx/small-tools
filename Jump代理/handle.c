#include "handle.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <fcntl.h>
#include "host_filter.h"
#include "ns_look_up.h"
#include "connect_tcp.h"
#include <sys/select.h>

#define HOST_NAME_MAX_LEN 128

void *handle(void *arg)
{
    pthread_detach(pthread_self());


    int client_sock = *(int*)arg;
    int server_sock;
    int return_value;
    char host_name[128];
    char buffer[BUFSIZ];
    char server_ip[INET_ADDRSTRLEN];
    free(arg);


    return_value = recv(client_sock, buffer, BUFSIZ, 0);
    if (return_value <= 0)
    {
        close(client_sock);
        fputs("recv 0 Byte from client...\n", stderr);
        pthread_exit(NULL);
    }
    printf("%s", buffer);

    if (!host_filter(buffer, host_name))
    {
        fputs("can't got host name from client!\n", stderr);
        close(client_sock);
        pthread_exit(NULL);
    }

    if (!ns_look_up(host_name, server_ip))
    {
        fputs("DNS Error!\n", stderr);
        close(client_sock);
        pthread_exit(NULL);
    }

    if ((server_sock = connect_tcp(server_ip, 80)) < 0)
    {
        fputs("connect server Error!\n", stderr);
        close(client_sock);
        pthread_exit(NULL);
    }
    else
    {
        return_value = send(server_sock, buffer, return_value, 0);
        if (return_value < 0)
        {
            perror("send");
        }
    }

    while (1)
    {
        fd_set sock_set;
        FD_ZERO(&sock_set);
        FD_SET(client_sock, &sock_set);
        FD_SET(server_sock, &sock_set);
        int count;
        int return_value;
        int max_fd_value = client_sock > server_sock?client_sock:server_sock;

        if ((return_value = select(max_fd_value + 1, &sock_set, NULL, NULL, NULL)) < 0)
        {
            perror("select");
            continue;
        }
        printf("select finished!");
        if (FD_ISSET(server_sock, &sock_set))
        {
            while ((count = read(server_sock, buffer, BUFSIZ)))
            {
                write(client_sock, buffer, count);
                if (count < BUFSIZ)
                    break;
                else if (count < 0)
                {
                    perror("server_sock write error!");
                    break;
                }
            }
        }

        if (FD_ISSET(client_sock, &sock_set))
        {
            while ((count = read(client_sock, buffer, BUFSIZ)))
            {
                write(server_sock, buffer, count);
                if (count < BUFSIZ)
                    break;
                else if (count < 0)
                {
                    perror("client_sock write error!");
                    break;
                }
            }
        }

    }
    return NULL;
}
