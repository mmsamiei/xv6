#include "types.h"
#include "stat.h"
#include "user.h"

void run(){
    for(int i=1; i<= 50 ; i++){
        printf(1, "process %d is printing for the %d time.\n", getpid(), i);
    }
}

int main(){
    printf(1, "father pid is %d\n", getpid());
    sleep(1000);
    int fork_val = fork();
    if(fork_val == -1){
        printf(1, "fork was faild\n");
    }
    else if(fork_val == 0){        //I am Child :)
        run();
        exit();
    } else {       //I am Father! :D
        run();
    }
    wait();
    exit();
}
