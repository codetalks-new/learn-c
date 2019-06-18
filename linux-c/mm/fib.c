#include<stdio.h>
#include<stdlib.h> // EXIT, EXIT_SUCCESS 常量等
#include<stdbool.h>
#include<stdint.h>
#include<assert.h> // 包含了 assert

/**
 * 一个简单的计算 fibonacci 数的程序
 * F0 = 0, F1 = 1
 * Fn = Fn-1 + Fn-2
 *
 */
#define FIB_BASE_CACHE_SIZE (1024)
static const char * const  GREETINGS = "欢迎使用 fib 一个 Fibonacci 小程序!\n";

static uint64_t fib_base_cache[FIB_BASE_CACHE_SIZE] = {0,1};
static uint64_t *fib_extra_cache;
static int max_cached_fib_n = 1;
static inline int max(int a,int b){
    return a > b ? a: b;
}


static void fill_fib_cache(){
    for(int i = 2; i < FIB_BASE_CACHE_SIZE; i++){
        fib_base_cache[i] = fib_base_cache[i-1] + fib_base_cache[i-2];
    }
    max_cached_fib_n = max(max_cached_fib_n,FIB_BASE_CACHE_SIZE -1);
}

static void fill_cache(int up_to){
    static bool fib_cache_has_filled = false;
    if(!fib_cache_has_filled){
        fib_cache_has_filled = true;
        fill_fib_cache();
    }
    if(up_to < FIB_BASE_CACHE_SIZE){
        return;
    }
    if(up_to <= max_cached_fib_n){
        return;
    }
    static int fib_extra_case_size = 0;
    int mul = (up_to - FIB_BASE_CACHE_SIZE)/FIB_BASE_CACHE_SIZE + 1;
    int extra_size = FIB_BASE_CACHE_SIZE * mul;
    if(fib_extra_case_size == 0){
        fib_extra_cache = calloc(extra_size,sizeof(uint64_t));
        fib_extra_case_size = extra_size;
    }else{
        fib_extra_cache = realloc(fib_extra_cache,extra_size);
    }

    int max_fib_n = FIB_BASE_CACHE_SIZE + extra_size;
    fib_extra_cache[0] = fib_base_cache[FIB_BASE_CACHE_SIZE -1] + fib_base_cache[FIB_BASE_CACHE_SIZE -2];
    fib_extra_cache[1] = fib_extra_cache[0] + fib_base_cache[FIB_BASE_CACHE_SIZE -1];
    int start_n = max(2, max_cached_fib_n - FIB_BASE_CACHE_SIZE);
    int end_n = extra_size;
    max_cached_fib_n = max(max_cached_fib_n, FIB_BASE_CACHE_SIZE + 2 - 1);
    for(int n = start_n; n < end_n; n++){
        fib_extra_cache[n] = fib_extra_cache[n-1] + fib_base_cache[n-2];
    }

}


uint64_t fib(int n){
    assert(n >= 0);
    if(n == 0){
        return 0;
    }
    fill_cache(n);
    if(n < FIB_BASE_CACHE_SIZE){
        return fib_base_cache[n];
    }else{
        int index = n - FIB_BASE_CACHE_SIZE;
        return fib_extra_cache[index];
    }


}

uint64_t fib_r(int n){
    assert(n >= 0);
    if(n < 2){
        return n;
    }
    return fib_r(n-1) + fib_r(n-2);
}



void print_usage(){
    printf("%s\n", GREETINGS);
    printf("Usage: ./fib <N> # 其中N是正整数\n");
}


int main(int argc, char *argv[]){
    int num = 0;
    if(argc < 2){
        print_usage();
        num = 2048;
    }else{
        num = atoi(argv[1]);
        if(num <= 0){
            print_usage();
            return -1;
        }
    }
    uint64_t result = fib(num);
    printf("FIB(%d)=%ld\n",num, result);
    return 0;
}
