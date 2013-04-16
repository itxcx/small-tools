#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

const char p[] = \
"You can use this program to listen a port.\n"
"It will print the message when the port had recived.\n"
"If you found any bug, please tell me, My Email is:\n"
"yucoat@yucoat.com\n"
"Usage: "
"listen_port <port>\n"
"                      --By YUCOAT\n";
int strtoint(const char* str)
{
    int value = 0;
    const char* p = str;
    if (strlen(str) > 5)
        return -1;
    while(*p != '\0')
    {
        if ((*p - '0' < 0) || (*p - '0' > 9))
            return -1;
        else
            value = value * 10 + (int)(*p - '0');
        p++;
    }
    if (value > 65535)
        return -1;
    return value;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("%s", p);
        return 1;
    }
    int port = strtoint(argv[1]);
    if (port < 0)
    {
        fprintf(stderr, "%s\n", "Port range is 0 ~ 65535");
        return 1;
    }

    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof sock_addr);
    sock_addr.sin_port = htons((in_port_t)port);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd;
    int sockopt = 1;    //socket option
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        perror("socket");
        return 1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
            &sockopt, sizeof(sockopt)) < 0)
    {
        perror("setsockopt");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(sockfd, 64) < 0)
    {
        perror("listen");
        return 1;
    }

    int rwsock;
    struct sockaddr_in client_addr;
    socklen_t sock_len = sizeof(client_addr);
    int  read_len;
    char buffer[BUFSIZ];
    while(1)
    {
        rwsock = accept(sockfd, (struct sockaddr*)&client_addr, &sock_len);
        if (rwsock < 0)
        {
            perror("accpet");
            break;
        }

        while((read_len = read(rwsock, buffer, BUFSIZ - 1)) >= 0)
        {
            buffer[read_len] = '\0';
            printf("%s", buffer);
            if (!read_len)
            {
                close(rwsock);
                break;
            }
        }
    }
    return 0;
}

