/**
 * By @代码会说话
 * 从汇编的角度看 C++ 中 extern "C" 的作用 及 C++ 函数重载的实现原理
 */
extern "C" {
int add(int a, int b) {
  return a + b;
}
}

double add(double a, double b) {
  return a + b;
}

int main() {
  return (add(3, 4));
}

/**
 * 汇编及代码清理
 * clang++ -S hello_extern_c.cpp&& sed -i bak -E '/^[[:space:]]*\./d'
 * hello_extern_c.s
 */