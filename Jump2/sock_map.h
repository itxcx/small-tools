#ifndef SOCK_MAP_H
#define SOCK_MAP_H
#include <pthread.h>

struct sock_map
{
    int client_sock;
    int server_sock;
    pthread_t client_thread;
    pthread_t server_thread;
};

#endif // SOCK_MAP_H
