#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
 *将程序设置成守护进程
 *      By YUCOAT(yucoat(at)yucoat.com)
 */
void setdaemon()
{

    pid_t pid;
    if(0 > (pid = fork())){
        fprintf(stderr, "%s@)%s:%d\n", strerror(errno), 
                __FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }else if(pid > 0){
        exit(EXIT_SUCCESS);
    }

    if(setsid() < 0) {
        fprintf(stderr, "%s@)%s:%d\n", strerror(errno), 
                __FUNCTION__, __LINE__);
        printf("gid:%d\tpid%d\n", (int)getgid(), (int)getpid());
        exit(EXIT_FAILURE);

    }

    int i;
    for(i = 0; i < 64; i++) {
        close(i);
    }

    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
}

/*
int main()
{
    setdaemon();
    return 0;
}
*/
