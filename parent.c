#include "types.h"
#include "user.h"
#include "syscall.h"
#include "traps.h"

int getppid() {
    int ppid ;
    asm volatile("int %1": "=a" ( ppid ) : "i" (T_SYSCALL) ,
            "a" ( SYS_getppid ) ) ;
    return ppid ;
}

int main(void) {
    int child_pid = fork();
    if(child_pid < 0)
        printf(1, "Fork failed %d\n", child_pid);
    else if (child_pid > 0) {
        printf(1, "I'm the parent my pid is %d child id is %d\n", getpid(), child_pid);
    } else {
        printf(1, "I'm the child my pid is %d my parent id is %d\n", getpid(), getppid());
    }
    exit();
}

