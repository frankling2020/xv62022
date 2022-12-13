#include "kernel/types.h"
#include "user/user.h"

int main(int args, char* argv[]){
    if (args != 2){
        fprintf(2, "Usage: sleep NUMBER[SUFFIX]"); 
        exit(1);
    }
    fprintf(0, "(nothing happens for a little while)\n");
    if (sleep(atoi(argv[1])) == 0) exit(0);
    else {
        fprintf(2, "SLEEP ERROR!"); 
        exit(1);
    }
}