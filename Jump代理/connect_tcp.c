#include "connect_tcp.h"

int connect_tcp(char *ip, int port)
{
    int sock;
    int retval;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((in_port_t)port);
    retval = inet_pton(AF_INET, ip, &(addr.sin_addr.s_addr));
    if (retval == 0)
    {
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    {
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        close(sock);
        return -1;
    }
    return sock;
}
