#include<stdio.h>
#include<stdlib.h>

extern char **environ;

void print_env(){
    // 1) 输出所有的环境变量
    for(char **env = environ;*env != NULL; env++){
        printf("%s\n",*env);
    }
}

int main(){
    print_env();
    printf("Author: Codetalks\n");
    clearenv();
    // 2) 增加一个环境变量
    putenv("BANXI=codetalks");
    // 3) 设置环境变量的的另一个接口
    setenv("AUTHOR","codetalks", 0);
    print_env();
    // 4) 根据名称取值
    printf("当前用户为:=%s\n",getenv("USER"));
    // 5) 删除一个环境变量
    unsetenv("BANXI");
    print_env();
}
