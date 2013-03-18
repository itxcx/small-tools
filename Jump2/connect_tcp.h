#ifndef CONNECT_TCP_H
#define CONNECT_TCP_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

int connect_tcp(char *ip, int port);

#endif // CONNECT_TCP_H
