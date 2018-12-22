#include <stdio.h>
#include <unistd.h>

int main(){
    int pid = fork();
    if(pid == -1){
        printf("failed to create process, error:%d\n", pid);
    }else if(pid == 0){
        printf("I'm the child process\n");
    }else{
        printf("I'm the parent process, child pid:%d\n",pid);
    }

    return 0;
}
