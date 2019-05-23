#include<stdio.h>
#include<stdlib.h> // EXIT, EXIT_SUCCESS 常量等
#include<stdbool.h>
#include<ctype.h> // 包含了 isdigit
#include<assert.h> // 包含了 assert
#include<string.h> // 包含了 strcmp ,strncmp

/**
 * 一个简单的计算 fibonacci 数的程序
 * F0 = 0, F1 = 1
 * Fn = Fn-1 + Fn-2
 *
 */
#define STR(x) #x
#define XSTR(x) STR(x)
#define FIB_CACHE_SIZE 8192
static const char * const  GREETINGS = "欢迎使用 fib 一个 Fibonacci 小程序!\n";

static const char * const  ERR_NO_ARG = "at least one argument needed\n";

static const char * const  ERR_NAN = "请输入一个1-" XSTR(FIB_CACHE_SIZE) "之间的数\n";

static int fib_cache[FIB_CACHE_SIZE] = {0,1};
static char* _PROGRAM_NAME;

static void fill_fib_cache(){
    for(int i = 2; i < FIB_CACHE_SIZE; i++){
        fib_cache[i] = fib_cache[i-1] + fib_cache[i-2];
    }
}

int fib(int n){
    assert(n >= 0 && n < 4096);
    if(n == 0){
        return 0;
    }
    return fib_cache[n];
}



bool is_valid_number(const char* input){
    if(input == NULL){
        return false;
    }
    int i = 0;
    for(const char *ch_ptr = input;*ch_ptr;++ch_ptr,++i){
        char ch = *ch_ptr;
        if(ch == '+' || ch == '-'){
            if(i == 0){
                continue;
            }else{
                return false;
            }
        }else if(isdigit(ch)){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

void print_usage(){
    printf("Usage: %s [+N]\n", _PROGRAM_NAME);
}

int parse_input_n(const char* input){
    if(!is_valid_number(input)){
        printf(ERR_NAN);
        return -1;
    }
    int n = atoi(input);
    if(n < 0){
        printf(ERR_NAN);
        return -1;
    }
    return n;
}


int main(int argc, char *argv[]){
    fill_fib_cache();
    printf(GREETINGS);
    _PROGRAM_NAME = argv[0];
    int n = -1;
    if(argc > 1){
        n = parse_input_n(argv[1]);
    }
    int count = 1;
    char input[128];
    while(true){
        if(*input){
            n = parse_input_n(input);
        }
        if(n > 0 && n < FIB_CACHE_SIZE){
            int fibn = fib(n);
            printf("FIB(%d) = %d\n",n, fibn);
        }
        printf("In [%d]:",count);
        scanf("%16s", input);
        count += 1;
        if(strcmp(input,"exit") == 0 || strcmp(input,"q") == 0){
            printf("\nBye Bye!\n");
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
