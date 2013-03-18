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
#include "sock_map.h"

#define SERVER_THREAD 0
#define CLIENT_THREAD 1

void *handle(void *arg)
{
    pthread_detach(pthread_self());
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    int sock;
    int recv_count = 0;
    int return_value;
    char buffer[BUFSIZ];
    struct sock_map* argument = (struct sock_map*)arg;
    int thread_type = argument->server_sock > 0 ? SERVER_THREAD:CLIENT_THREAD;

    if (SERVER_THREAD == thread_type)
    {
        sock = argument->server_sock;
    }
    else
    {
        sock = argument->client_sock;
    }

    // server thread
    if (SERVER_THREAD == thread_type)
    {
        while ((recv_count = read(sock, buffer, BUFSIZ)) > 0)
        {
            write(argument->client_sock, buffer, recv_count);
        }
        pthread_cancel(argument->client_thread);
        close(argument->client_sock);
        close(argument->server_sock);
        free(argument);
        pthread_exit(NULL);
    }

    // client thread
    else
    {
        int port;
        char host_name[128];
        char server_ip[INET_ADDRSTRLEN];

        recv_count = recv(sock, buffer, BUFSIZ, 0);
        if (recv_count <= 0)
        {
            perror("recv");
            free(arg);
            close(sock);
            pthread_exit(NULL);
        }
        if (!host_filter(buffer, host_name, &port))
        {
            perror("host_filter");
            free(arg);
            close(sock);
            pthread_exit(NULL);
        }

        if (!ns_look_up(host_name, server_ip))
        {
            perror("ns_look_up");
            free(arg);
            close(sock);
            pthread_exit(NULL);
        }
        port = (port == 0) ? 80 : port;
        if ((argument->server_sock = connect_tcp(server_ip, port)) < 0)
        {
            perror("connect_tcp");
            free(arg);
            close(sock);
            pthread_exit(NULL);
        }
        else
        {
            return_value = pthread_create(&(argument->server_thread), NULL, handle, arg);
            if (return_value < return_value)
            {
                perror("pthread_create");
                free(arg);
                close(sock);
                pthread_exit(NULL);
            }
            write(argument->server_sock, buffer, recv_count);
            while((recv_count = read(argument->client_sock, buffer, BUFSIZ)) > 0)
            {
                write(argument->server_sock, buffer, recv_count);
            }
            pthread_cancel(argument->server_thread);
            close(argument->client_sock);
            close(argument->server_sock);
            free(argument);
            pthread_exit(NULL);
        }
    }
    return NULL;
}
