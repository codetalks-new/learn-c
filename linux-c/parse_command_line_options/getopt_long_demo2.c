#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

static struct option long_options [] = {
    { .name = "add", .has_arg = required_argument, .flag = 0, .val = 0},
    { .name = "append", .has_arg = no_argument, .flag = 0, .val = 0},
    { .name = "delete", .has_arg = required_argument, .flag = 0, .val = 0},
    { .name = "verbose", .has_arg = no_argument, .flag = 0, .val = 0},
    { .name = "create", .has_arg = required_argument, .flag = 0, .val = 0},
    { .name = "file", .has_arg = required_argument, .flag = 0, .val = 0},
    { .name = 0, .has_arg = 0, .flag = 0, .val = 0},
};

int main(int argc, char *argv[])
{
   int c;
   int digit_optind = 0;
   while(true){
       int this_option_optind = optind ? optind: 1;
       int option_index = 0;
       c = getopt_long(argc, argv,"abc:d:012", long_options,&option_index);
       if(c == -1){
           break;
       }
       switch (c) {
           case 0:
               printf("option %s", long_options[option_index].name);
               if(optarg){
                   printf(" with arg %s\n", optarg);
               }
               printf("\n");
               break;
           case '0':
           case '1':
           case '2':
               if(digit_optind != 0 && digit_optind != this_option_optind){
                   printf("digits occur in two different argv-elements.\n");
               }
               digit_optind = this_option_optind;
               printf("option %c\n", c);
               break;
           case 'a':
               printf("option a\n");
               break;
           case 'b':
               printf("option b\n");
               break;
           case 'c':
               printf("option c with value '%s'\n", optarg);
               break;
           case 'd':
               printf("option d with value '%s'\n", optarg);
               break;
           case '?':
               break;
           default:
               printf("?? getopt returned character code 0%o??\n", c);
               
       }
   }
   if(optind < argc){
       printf("no-option ARGV-elements:\n");
       while(optind < argc){
           printf("%s\n", argv[optind++]);
       }
       printf("\n");
   }
   exit(EXIT_SUCCESS);
}
