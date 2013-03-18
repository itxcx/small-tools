#include "ns_look_up.h"

char *ns_look_up(char *domain, char *ip)
{
    struct addrinfo addr;
    memset(&addr, 0, sizeof addr);

    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_protocol = IPPROTO_TCP;

    struct addrinfo *addr_list;
    getaddrinfo(domain, "80", &addr, &addr_list);
    struct addrinfo *p = addr_list;

    if (NULL == p)
    {
        freeaddrinfo(addr_list);
        return NULL;
    }
    else
    {
        void *addr_ptr = &(((struct sockaddr_in*)p->ai_addr)->sin_addr);
        inet_ntop(p->ai_addr->sa_family, addr_ptr, ip, INET_ADDRSTRLEN);
    }
    freeaddrinfo(addr_list);
    return ip;
}

