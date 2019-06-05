#include<stdio.h>
#include<unistd.h> // 包含了 getpid ,sbrk
#include<stdlib.h> // EXIT, EXIT_SUCCESS 常量等
#include<stdbool.h>
#include<ctype.h> // 包含了 isdigit
#include<assert.h> // 包含了 assert
#include<string.h> // 包含了 strcmp ,strncmp

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
int alloc_size = 8 * 1024;// 默认8K
#define HEAP_BLOCK_MAX_COUNT   (2048)
static void * allocated_heap[HEAP_BLOCK_MAX_COUNT];
int allocated_count = 0;

int prompt_alloc_block_count(){
    int max_count = HEAP_BLOCK_MAX_COUNT - allocated_count;
    while(1){
        printf("请输入要分配的堆内存块数(max:%d)>", max_count);
        int count = 0;
        scanf(" %d",&count);
        if(count < 1 || count > max_count){
            printf("输入块数值:%d 过大或过小,请重新输入\n",count);
        }else{
            return count;
        }
    }
}

void alloc_heap_memory(){
    int count = prompt_alloc_block_count();
    int kbs = alloc_size / 1024;
    printf("正在分配堆内存...\n");
    for(int i  = 0;i < count; i++){
        int index = allocated_count + i;
        int total_count = index + 1;
        void *addr = malloc(alloc_size);
        //void *addr = sbrk(alloc_size);
        allocated_heap[index]  = addr;
        printf("分配第 %d 块堆内存,大小 %dKB, 地址:%p\n",total_count,kbs, addr);
    }
    allocated_count += count;
}

int prompt_free_block_index(){
    int max_no = allocated_count;
    while(1){
        printf("请输入要释放的堆内存块序号[1,%d]>", max_no);
        int no = 0;
        scanf(" %d",&no);
        if(no < 1 || no > max_no){
            printf("输入的序号值:%d 过大或过小,请重新输入\n",no);
        }else{
            int index = no - 1;
            if(allocated_heap[index]){
                return index;
            }else{
                printf("输入的序号:%d 堆内存块,未分配内存或已经释放了,请重新输入\n",no);
            }
        }
    }
}

void prompt_block_size(){
    int kbs = alloc_size / 1024;
    while(1){
        printf("当前块大小:%dKB, 请输入新的块的大小(单位KB)>",kbs);
        int mul = 0;
        scanf(" %d", &mul);
        if(mul < 1 || mul > 80000){
            printf("输入的块大小:%dKB, 太小或太大,请重新输入\n",mul);
        }else{
            alloc_size = mul * 1024;
            break;
        }
    }
}


void free_heap_memory(){
    int index = prompt_free_block_index();
    void *addr = allocated_heap[index];
    if(addr){
        free(addr);
        printf("索引为 %d, 位于 %p 位置的内存块已经释放\n",index, addr);
        allocated_heap[index] = NULL;
    }
}

void print_main_menu(){
    printf("请输入需要执行的菜单项(输入q退出)?:\n");
    printf("(A):分配堆内存块\n");
    printf("(B):释放堆内存块\n");
    printf("(C):设置分配的块大小(KB)\n");
}

void hello_heap_cli(){
    char ch;
    while(1){
        print_main_menu();
        scanf(" %c",&ch);
        if(ch == 'A' || ch == 'a'){
            alloc_heap_memory();
        }else if(ch == 'B' || ch == 'b'){
            free_heap_memory();
        }else if(ch == 'C' || ch == 'c'){
            prompt_block_size();
        }else if(ch == 'Q' || ch == 'q'){
            printf("Bye Bye!\n");
            exit(EXIT_SUCCESS);
            break;
        }

    }

}
int main(int argc, char *argv[])
{
    int local = 18;
    caches[0] = 0;
    printf("Hello World! 当前进程编号是: %d\n",getpid());
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
    //printf("按任意键退出!\n");
    //getchar();
    hello_heap_cli();
    return 0;
}
