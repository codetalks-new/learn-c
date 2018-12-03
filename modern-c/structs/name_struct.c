/**
 * @抖音 代码会说话
 */

#include <stdio.h>

typedef struct User {
  char *name;  // 名字
  int age;     // 年龄
  int salary;  // 工资
  char gender; // 性别
} User;

void print_user(User *u) {
  printf("+------+------+-----+\n");
  printf(" %s\t%d\t%d\t%c\n", u->name, u->age, u->salary, u->gender);
  printf("+------+------+-----+\n");
}

int main(int argc, char const *argv[]) {
  User u = {.name = "banxi", .age = 18, .salary = 3000, .gender = 'm'};
  print_user(&u);
  return 0;
}
