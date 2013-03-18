#include "host_filter.h"

char *host_filter(char *str, char *dst, int *port)
{
    char *p = str;
    char *dst_p = dst;
    char *tail = str + strlen(str);
    *port = 0;
    while (strncmp(p, "Host", 4) &&
           (tail - p >(signed)strlen("Host:  \r\n\r\n")))
    {
        p++;
    }
    if (tail - p <= (signed)strlen("Host:  \r\n\r\n"))
        return NULL;
    else
    {
        int flag = 0;
        p += strlen("Host: ");
        while (*p != '\r')
        {
            if (*p == ':')
            {
                flag = 1, p++;
                continue;
            }
            if (flag == 0)
                *(dst_p++) = *(p++);
            else
                *port = *port * 10 + ((*p++) - '0');
        }
        *dst_p = '\0';
        return dst;
    }
}
