#include <stdio.h>
#include "setupTcp.h"
#include <stdlib.h>
#include <pthread.h>
#include "handle.h"
#include "sock_map.h"

int main(void)
{
    int proxy_sock = setup_tcp(8888);
    if (proxy_sock < 0)
    {
        perror("setup_tcp");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        struct sockaddr_in clientAddr;
        socklen_t sockLength = sizeof(clientAddr);
        pthread_t thread;
        int return_value;

        struct sock_map *sock_pair= (struct sock_map*)malloc(sizeof(struct sock_map));
        if (sock_pair == NULL)
        {
            perror("malloc");
            continue;
        }
        sock_pair->client_sock = -1;
        sock_pair->server_sock = -1;



        sock_pair-> client_sock = accept(proxy_sock, (struct sockaddr*)&clientAddr, &sockLength);
        if (sock_pair->client_sock < 0)
        {
            perror("accept");
            continue;
        }

        return_value = pthread_create(&thread, NULL, handle, (void*)sock_pair);
        if (return_value < 0)
        {
            perror("pthread_create");
        }
    }
    return 0;
}

