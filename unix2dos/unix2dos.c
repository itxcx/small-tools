/*
 *author:YUCOAT(thlgood@yucoat.com)
 *data:2013-9-6
 *comment: Convert UNIX/Windows new line style
 */
#include <stdio.h>
#include <getopt.h>

char* const help_msg = 
"\nuw -- New line Convert tool\n"
"\n"
"Usage:\n"
"    uw -u, --unixfile filepath          Covernt Unix new line(LF) to Windows new line(CRLF)\n"
"    uw -w, --windowsfile filepath       Covernt Windows new line(CRLF) to Unix line(LF)\n"
"\n"
"\n"
"My E-mail(thlgood@yucoat.com)\n";


#define LF      0xa
#define CR      0xd
#define U2W     1
#define W2U     2

int parser_arg(int argc, char* argv[], char** srcfile, int* convert_type);

int main(int argc, char* argv[])
{
    char*   srcfile = NULL;
    int     cvt_type = 0;

    int retval = parser_arg(argc, argv, &srcfile, &cvt_type);
    if (retval) {
        return retval;
    }

    FILE* srcfp = fopen(srcfile, "rb");
    if (!srcfile) {
        return 2;
    }

    char temp = 0;

    while((temp = fgetc(srcfp)) != EOF) 
    {
        if (U2W == cvt_type  && LF == temp) {
            printf("\r\n");
            continue;
        }
        else if (W2U == cvt_type && CR == temp) {
            continue;
        }
        putchar(temp);
    }

    fclose(srcfp);

    return 0;
}


int parser_arg(int argc, char* argv[], char** srcfile, int* convert_type)
{
    if (!srcfile || !convert_type)
    {
        return 2;
    }

    const struct option long_options[] = {
        {"unixfile",    1, NULL, 'u'},
        {"windowsfile", 1, NULL, 'w'},
        {"help",        0, NULL, 'h'},
        {NULL,          0, NULL, 0  }
    };

    const char* short_options = "u:w:h";
    int next_opt = 0;

    do {
        next_opt = getopt_long(argc, argv, short_options, long_options, NULL);

        switch(next_opt) {
        case 'h':
            printf("%s", help_msg);
            return 0;
            break;

        case 'u':
            if (*convert_type) {
                printf("%s", help_msg);
                return 1;
            }
            *convert_type = U2W;
            *srcfile = optarg;
            break;

        case 'w':
            if (*convert_type) {
                printf("%s", help_msg);
                return 1;
            }
            *convert_type = W2U;
            *srcfile = optarg;
            break;
        
        case -1:
            break;

        default:
            printf("%s", help_msg);
            return 1;
        }

    }while(next_opt != -1);

    if (NULL == *srcfile) {
        printf("%s", help_msg);
        return 1;
    }

    return 0;
}
