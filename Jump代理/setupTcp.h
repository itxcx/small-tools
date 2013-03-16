#ifndef SETUPTCP_H
#define SETUPTCP_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#define MAXPENDING 1024
int setup_tcp(int port);

#endif // SETUPTCP_H
