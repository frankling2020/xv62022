#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int p[2];
    pipe(p);
    
    int pid;
    if (fork() == 0){
        pid = getpid();
        char buf[4];
        if (read(p[0], buf, 4) != 4){
            fprintf(2, "failed to read in child\n");
            exit(1);
        }
        close(p[0]);
        printf("%d: received %s\n", pid, buf);
        if (write(p[1], "pong", 4) != 4){
            fprintf(2, "failed to write in child\n");
            exit(1);
        }
        close(p[1]);
    } else {
        pid = getpid();
        if (write(p[1], "ping", 4) != 4){
            fprintf(2, "failed to write in parent\n");
            exit(1);
        }
        close(p[1]);
        char buf[4];

        // wait for children to return
        wait(0);
        if (read(p[0], buf, 4) != 4){
            fprintf(2, "failed to read in parent\n");
            exit(1);
        }
        printf("%d: received %s\n", pid, buf);
        close(p[0]);
    }
    exit(0);
}