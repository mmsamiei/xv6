#define NUM_OF_PROCS 30

#include "types.h"
#include "stat.h"
#include "user.h"

int cid[NUM_OF_PROCS];
int pid[NUM_OF_PROCS];

int find_cid(int pid_number){
    for(int i = 0; i < NUM_OF_PROCS; i++){
        if(pid[i] == pid_number){
            return i;
        }
    }
    return -1;
}

void run(int cid){
    for(int i = 1 ; i <= 50; i++ ){
        printf(1, "Child %d prints for the  %d time.\n", cid, i);
    }

}

int main(){

    for(int i = 0; i < NUM_OF_PROCS; i++){
        int fork_val = fork();
        if(fork_val == -1){
            printf(1,"fork was faild");
        }
        else if(fork_val == 0){      //means that i am child
            cid[i] = i;
            if(cid[i] % 3 == 1) {
                nice();
            } else if(cid[i] % 3 == 2) {
                nice();
                nice();
            }
            run(cid[i]);      //run the process of child
            exit();     //to prevent do fork from child process
        } else {   //means that i am God Parent
            pid[i] = fork_val;
        }

    }

    int child_output[NUM_OF_PROCS][3];
    for(int i = 0; i < NUM_OF_PROCS; i++){
        int child_pid;
        int wtime, rtime;
        child_pid = wait2(&wtime, &rtime);
        child_output[i][0] = child_pid;
        child_output[i][1] = wtime + rtime;
        child_output[i][1] = wtime;
    }

    printf(1, "Printing all children\n");
    for(int i = 0; i < NUM_OF_PROCS; i++){
        printf(1, "Child cid: %d  turn around time: %d \n", find_cid(child_output[i][0]), child_output[i][1], child_output[i][2]);
    }


    int amount = 0;
    int num = 0;
    for(int i = 0; i < NUM_OF_PROCS; i++){
        if(find_cid(child_output[i][0]) % 3 == 0){
            amount += child_output[i][1];
            num++;
        }
    }

    printf(1, "Printing Group GRT %d \n", (amount) / num);

    amount = 0;
    num = 0;
    for(int i = 0; i < NUM_OF_PROCS; i++){
        if(find_cid(child_output[i][0]) % 3 == 1){
            amount += child_output[i][1];
            num++;
        }
    }
    printf(1, "Printing Group FRR %d \n", (amount) / num);

    amount = 0;
    num = 0;
    for(int i = 0; i < NUM_OF_PROCS; i++){
        if(find_cid(child_output[i][0]) % 3 == 2){
            amount += child_output[i][1];
            num++;
        }
    }
    printf(1, "Printing Group RR %d \n", (amount) / num);

    exit();
}
