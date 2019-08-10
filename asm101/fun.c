
void fun_noop() {}

long fun0() {
  return 41;
}
long fun1(long a) {
  return a;
}
long fun1_tmp(long a) {
  long tmp = a;
  return tmp;
}

long fun2(long a, long b) {
  return a + b;
}

long fun3(long a, long b, long c) {
  return fun2(a, b) + c;
}
long fun4(long a, long b, long c, long d) {
  return fun3(a, b, c) + d;
}
long fun5(long a, long b, long c, long d, long e) {
  return fun4(a, b, c, d) + e;
}
long fun6(long a, long b, long c, long d, long e, long f) {
  return a + b + c + d + e + f;
}
long fun7(long a, long b, long c, long d, long e, long f, long g) {
  return a + b + c + d + e + f + g;
}
long fun8(long a, long b, long c, long d, long e, long f, long g, long h) {
  return a + b + c + d + e + f + g + h;
}

typedef struct User {
  long age;
  long sex;
  long weight;
} User;

long get_age(User user) {
  return user.age;
}

long get_sex(User *user_ptr) {
  return user_ptr->sex;
}

int main() {
  long (*fun_ptr)() = fun1_tmp;
  return fun_ptr(3);
}