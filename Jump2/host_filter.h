#ifndef HOST_FILTER_H
#define HOST_FILTER_H

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

char *host_filter(char *str, char *dst, int *port);

#endif // HOST_FILTER_H
