#ifndef NS_LOOK_UP_H
#define NS_LOOK_UP_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

char *ns_look_up(char *domain, char *ip);

#endif // NS_LOOK_UP_H
