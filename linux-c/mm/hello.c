#include<stdio.h>

const char *greetings = "All You Need Is Love\n";
const char *greetings1 = "All You Need Is Love\n";
const char *greetings2 = "All You Need Is Love\n";
const char *greetings3 = "All You Need Is Love\n";
const char *greetings5 = "All You Need Is Love\n";
const char *greetings6 = "All You Need Is Love\n";
const char *greetings7 = "All You Need Is Love\n";
const char *greetings8 = "All You Need Is Love\n";

int caches[1000 * 1024];
int primes_caches[] = {2,3,5,7,11,13,17,19,23,};
int buffer[1000 * 1024];

void fun_r(int depth){
    int local = 18;
    printf("fun_r(%d) local 的地址 %p\n",depth, &local);
    if(depth < 4){
        fun_r(depth + 1);
    }
}
int main(int argc, char *argv[])
{
    int local = 18;
    caches[0] = 0;
    printf("Hello World!\n");
    printf("argc  的地址 %p\n",&argc);
    printf("argv  的地址 %p\n",argv);
    printf("local 的地址 %p\n",&local);
    printf("main      的地址 %p\n",&main);
    printf("fun_r     的地址 %p\n",&fun_r);
    printf("printf     的地址 %p\n",&printf);
    printf("getchar     的地址 %p\n",&getchar);
    printf("greetings     的地址 %p\n",&greetings);
    printf("caches        的地址 %p\n",&caches);
    printf("primes_caches 的地址 %p\n",&primes_caches);
    printf("buffer        的地址 %p\n",&buffer);
    fun_r(1);
    printf("按任意键退出!\n");
    getchar();
    return 0;
}
