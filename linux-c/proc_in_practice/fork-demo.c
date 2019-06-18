#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if(pid == -1){
        printf("failed to create process, error:%d\n", pid);
    }else if(pid == 0){
        printf("I'm the child process\n");
        getchar();
    }else{
        printf("I'm the parent process, child pid:%d\n",pid);
        getchar();
        wait(NULL);
    }

    return 0;
}
