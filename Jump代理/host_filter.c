#include "host_filter.h"

char *host_filter(char *str, char *dst)
{
    char *p = str;
    char *dst_p = dst;
    char *tail = str + strlen(str);
    while (strncmp(p, "Host", 4) &&
           (tail - p >(signed)strlen("Host:  \r\n\r\n")))
    {
        p++;
    }
    if (tail - p <= (signed)strlen("Host:  \r\n\r\n"))
        return NULL;
    else
    {
        p += strlen("Host: ");
        while (*p != '\r')
        {
            *(dst_p++) = *(p++);
        }
        *dst_p = '\0';
        return dst;
    }
}
