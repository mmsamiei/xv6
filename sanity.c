#include "types.h"
#include "stat.h"
#include "user.h"

void run(int cid){
    for(int i = 1 ; i <= 500; i++ ){
        printf(1, "Child %d prints for the  %d time.\n", getpid(), cid);
    }

}

int main(){
    int cid[29];

    for(int i = 0; i < 30; i++){
        int fork_val = fork();
        if(fork_val == -1){
            printf(1,"fork was faild");
        }
        else if(fork_val == 0){      //means that i am child
            cid[i] = i;
            if(cid[i] % 3 == 0) {
                nice();
            } else if(cid[i] % 3 == 0) {
                nice();
                nice();
            }
            run(cid[i]);      //run the process of child
            exit();     //to prevent do fork from child process
        }
        else{   //means that i am God Parent
            //so do nothing
        }

    }

    int child_output[30][3];
    for(int i=0;i<30;i++){
        int child_pid;
        int wtime,rtime;
        child_pid = wait2(&wtime,&rtime);
        child_output[i][0]=child_pid;
        child_output[i][1]=wtime;
        child_output[i][2]=rtime;
    }

    for(int i=0;i<10;i++){
        printf(1,"child pid: %d         wait time: %d        running time : %d \n",child_output[i][0],child_output[i][1],child_output[i][2]);

    }


    exit();
}
