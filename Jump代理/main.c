#include <stdio.h>
#include "setupTcp.h"
#include <stdlib.h>
#include <pthread.h>
#include "handle.h"

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
        int *client_sock = (int *)malloc(sizeof(int));
        struct sockaddr_in clientAddr;
        socklen_t sockLength = sizeof(clientAddr);
        pthread_t thread;
        int return_value;

        *client_sock = accept(proxy_sock, (struct sockaddr*)&clientAddr, &sockLength);
        if (*client_sock < 0)
        {
            perror("accept");
            continue;
        }

        return_value = pthread_create(&thread, NULL, handle, (void*)client_sock);
        if (return_value < 0)
        {
            perror("pthread_create");
        }
    }
    return 0;
}

