#include <stdio.h>
#include <stdint.h>
#include <string.h>

const char * const greetings = "Hi,All You Need is Love!";
// 100 以内质数表
const uint64_t primies[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
// 2048 以内的 Fibonacci 数
#define FIBS_SIZE (2048)
uint64_t fibs[FIBS_SIZE];

void fill_fibs(){
    // Fn = Fn-1 + Fn-2
    fibs[0] = 0;
    fibs[1] = 1;
    for(int n = 2; n < FIBS_SIZE; n++){
        fibs[n] = fibs[n-1] + fibs[n-2];
    }
}

void fun_r(int depth){
    int local = 248;
    printf("fun_r(%d) depth 地址:%p\n",depth, &depth);
    printf("fun_r(%d) local 地址:%p\n",depth, &local);

    if(depth > 3){
        return;
    }
    fun_r(depth+1);
}


int main(int argc, char *argv[])
{
    uint64_t main_var1 = 1024;
    uint64_t val_holder1 = 0;
    uint64_t val_holder2 = 0;
    uint64_t val_holder3 = 0;
    uint64_t val_holder4 = 0;
    uint64_t val_holder5 = 0;
    uint64_t *ptr = &main_var1;
    uint64_t *ptr2 = &main_var1;
    memcpy(&val_holder1,++ptr, sizeof ptr);
    memcpy(&val_holder2,++ptr, sizeof ptr);
    *ptr = 3;
    memcpy(&val_holder3,++ptr, sizeof ptr);
    memcpy(&val_holder4,++ptr, sizeof ptr);
    memcpy(&val_holder5,++ptr, sizeof ptr);
    printf("%s\n", greetings);
    printf("数据段地址:\n");
    printf("全局变量 greetings   的地址是:%p\n",greetings);
    printf("全局变量 primies     的地址是:%p\n",primies);
    printf("全局变量 fibs        的地址是:%p\n",fibs);
    printf("代码段地址:\n");
    printf("函数     main        的地址是:%p\n",main);
    printf("函数     fill_fibs   的地址是:%p\n",fill_fibs);
    printf("函数     fun_r       的地址是:%p\n",fun_r);
    printf("函数     printf      的地址是:%p\n",printf);
    printf("栈地址:\n");
    printf("入口参数 argv        的地址是:%p\n",argv);
    printf("入口参数 argc        的地址是:%p\n",&argc);
    printf("入口参数 argc        的值  是:%d\n",argc);
    printf("局部变量 main_var1   的地址是:%p\n",&main_var1);
    printf("局部变量 main_var1+1 的地址是:%p\n",++ptr2);
    printf("局部变量 main_var1+2 的地址是:%p\n",++ptr2);
    printf("局部变量 main_var1+3 的地址是:%p\n",++ptr2);
    printf("局部变量 main_var1+4 的地址是:%p\n",++ptr2);
    printf("局部变量 main_var1+5 的地址是:%p\n",++ptr2);
    printf("局部变量 main_var1+5   的值是:0x%lx\n",val_holder5);
    printf("局部变量 main_var1+4   的值是:0x%lx\n",val_holder4);
    printf("局部变量 main_var1+3   的值是:0x%lx\n",val_holder3);
    printf("局部变量 main_var1+2   的值是:0x%lx\n",val_holder2);
    printf("局部变量 main_var1+1   的值是:0x%lx\n",val_holder1);
    fill_fibs();
    printf("FIB(%d) = %ld\n", 64, fibs[64]);
    printf("fun_r 栈地址1:\n");
    fun_r(1);
    printf("fun_r 栈地址2:\n");
    fun_r(1);
    printf("按任意键退出!\n");
    getchar();
    return 0;
}
