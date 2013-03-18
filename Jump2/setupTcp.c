#include "setupTcp.h"
#include <unistd.h>

int setup_tcp(int port)
{
    int proxySock;
    int retval;
    struct sockaddr_in proxyAddr;

    memset(&proxyAddr, 0, sizeof(proxyAddr));
    proxyAddr.sin_family = AF_INET;
    proxyAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    proxyAddr.sin_port = htons((in_port_t)port);

    proxySock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (proxySock < 0)
    {
        perror("socket");
        return -1;
    }


    if (bind(proxySock, (struct sockaddr*) & proxyAddr, sizeof(proxyAddr)) < 0)
    {
        perror("bind");
        close(proxySock);
        return -1;
    }

    if (listen(proxySock, MAXPENDING) < 0)
    {
        perror("listen");
        close(proxySock);
        return -1;
    }

    int opt = 1;
    retval = setsockopt(proxySock, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
    if (retval < 0)
    {
        perror("setsocketopt");
        close(proxySock);
        return -1;
    }
    return proxySock;
}
