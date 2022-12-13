#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_pipe(int p[2]){
    int prime;
    int n;
    close(p[1]);

    if (read(p[0], &prime, 4) != 4) exit(0);

    printf("prime %d\n", prime);
    
    int new_p[2];
    pipe(new_p);
    if (fork() == 0){
        prime_pipe(new_p);
    }
    else {
        close(new_p[0]);
        while (read(p[0], &n, 4)){
            if (n % prime) write(new_p[1], &n, 4);
        }
        close(p[0]);
        close(new_p[1]);
        wait(0);
    } 
    exit(0);
}


int main(int args, char* argv[]){
    int p[2];
    pipe(p);

    if (fork() == 0) {
        prime_pipe(p);
    } else {
        close(p[0]);
        for (int x=2; x<=35; ++x){
            if (write(p[1], &x, 4) != 4){
                fprintf(2, "Error to write");
                exit(1);
            }
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
    return 0;
}