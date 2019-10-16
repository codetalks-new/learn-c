/**
 * 简单的 C语言单元测试工具库
 * 支持 macOS/Linux
 *
 */
#pragma once
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <libgen.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// 测试用例
typedef struct Test {
  // 测试用例名称
  const char* name;
  // 测试函数指针
  void (*fun)();
} Test;
// 测试状态
typedef enum TestStatus {
  // 运行中
  TestStatusRun = 1,
  // 成功
  TestStatusSuccess = 2,
  // 失败
  TestStatusFailure = 4,
} TestStatus;

// 测试用例运行详情
typedef struct TestDetal {
  TestStatus status;
  double duration;
} TestDetail;

// 程序运行时间统计的计时类型,用于统计进程耗时
static clockid_t clockid = CLOCK_PROCESS_CPUTIME_ID;
typedef struct TestTimer {
  // 开始时间
  struct timespec start;
  // 结束时间
  struct timespec end;

} TestTimer;

static TestTimer _timer = {.start = {}, .end = {}};

// 计算耗时,单位毫秒
static double _timer_calc_ms() {
  double start =
      (double)_timer.start.tv_sec + (double)_timer.start.tv_nsec * 10e-9;
  double end = (double)_timer.end.tv_sec + (double)_timer.end.tv_nsec * 10e-9;
  return (end - start) * 1000;
}

// 开始计时
static void _timer_start() {
  clock_gettime(clockid, &_timer.start);
}

// 停止计时
static void _timer_stop() {
  clock_gettime(clockid, &_timer.end);
}

// 显示当前计时器耗时
static void _timer_print_ms() {
  printf("%.6lf ms(毫秒)", _timer_calc_ms());
}

// 终端输出的颜色表,红色代表失败,绿色代表成功
typedef struct Colors {
  const char* green;
  const char* red;
  const char* green_dark;
  const char* red_dark;
  const char* normal;
  const char* normal_dark;
} Colors;

static Colors colors = {
    .green = "\033[0;32m",
    .green_dark = "\033[1;32m",
    .red = "\033[0;31m",
    .red_dark = "\033[1;31m",
    .normal = "\033[0m",
    .normal_dark = "\033[1m",
};

static int _color_print(const char* color, const char* fmt, ...) {
  va_list args;
  char buffer[256];
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  printf("%s", color);
  int n = printf("%s", buffer);
  printf("%s", colors.normal);
  return n;
}

// 测试信息输出级别
typedef enum VerboseLevel {
  // 安静模式
  VerboseLevelSilent = 0,
  // 简单模式,每一个测试输出一行
  VerboseLevelSimple = 1,
  // 默认模式,每一个测试输出一行,并加上错误条件
  VerboseLevelDefault = 2,
  // 详尽模式,每一个测试输出一行,并尽可能输出详细信息
  VerboseLevelVerbose = 3
} VerboseLevel;

typedef struct TestOptions {
  // 日志输出级别,默认为 Default 级别
  VerboseLevel verbose_level;
  // 禁用子进程执行模式,默认为启用
  bool no_exec;
} TestOptions;

// 测试信息输出级别全局变量
static TestOptions _opts = {.verbose_level = VerboseLevelVerbose,
                            .no_exec = false};
// 指向当前正在进行的单元测试
static const struct Test* _current_test = NULL;
// 当前测试用例在测试用户数组中对应的索引
static int _current_index = -1;
//当前测试用例日志输出数
static int _current_unit_log_cnt = 0;
//当前测试用例断言失败次数
static int _current_unit_fail_cnt = 0;
// 每一个单元测试用例下面可以注释多个 case,这用来保存当前 case 名称
static char _current_case_name[64] = "";
// 当前 case 日志输出数
static int _current_case_log_cnt = 0;

static void _test_line_indent(int level) {
  static const char* spaces = "        ";
  int n = level * 2;
  while (n > 8) {
    printf("%s", spaces);
    n -= 8;
  }
  printf("%.*s", n, spaces);
}

#define MIN_WIDTH (48)
static void _test_begin_line(const Test* t) {
  const VerboseLevel level = _opts.verbose_level;
  if (level == VerboseLevelSilent) {
    _current_unit_log_cnt = 1;
    return;
  }
  const char* format =
      level == VerboseLevelVerbose ? "Test %s:\n" : "Test %s... ";
  int n = _color_print(colors.normal_dark, format, t->name);
  if (n < MIN_WIDTH && level < VerboseLevelVerbose) {
    char spaces[MIN_WIDTH];
    memset(spaces, ' ', MIN_WIDTH);
    printf("%.*s", MIN_WIDTH - n, spaces);
  } else {
    _current_unit_log_cnt++;
  }
}

static void _test_end_line(bool success) {
  const char* status_text = success ? "OK" : "FAILED";
  const char* color = success ? colors.green_dark : colors.red_dark;
  printf("[ ");
  _color_print(color, status_text);
  printf(" ]");
  if (success) {
    printf("  ");
    _timer_print_ms();
  }
  printf("\n");
}

static void _test_error(const char* fmt, ...) {
  const VerboseLevel level = _opts.verbose_level;
  if (level == VerboseLevelSilent) {
    return;
  }
  if (level <= VerboseLevelDefault && !_current_unit_log_cnt && _current_test) {
    printf("[ ");
    _color_print(colors.red_dark, "FAILED");
    printf(" ]\n");
  }
  if (level >= VerboseLevelDefault) {
    _test_line_indent(1);
    if (level >= VerboseLevelVerbose) {
      _color_print(colors.red_dark, "ERROR:");
    }
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
  }
  if (level >= VerboseLevelVerbose) {
    printf("\n");
  }
}

// 测试断言
int _test_check_(bool cond, const char* file, int line, const char* fmt, ...) {
  const char* result_str = cond ? "OK" : "FAILED";
  const char* result_color = cond ? colors.green : colors.red;
  const VerboseLevel level = cond ? VerboseLevelVerbose : VerboseLevelDefault;
  if (!cond) {
    if (_current_test && !_current_unit_log_cnt) {
      _test_end_line(-1);
    }
    _current_unit_fail_cnt++;
    _current_unit_log_cnt++;
  }
  if (_opts.verbose_level >= level) {
    const bool has_case = !!_current_case_name[0];
    if (has_case && !_current_case_log_cnt) {
      _test_line_indent(1);
      _color_print(colors.normal_dark, "Case %s:\n", _current_case_name);
      _current_case_log_cnt++;
      _current_unit_log_cnt++;
    }
    _test_line_indent(has_case ? 2 : 1);
    if (file) {
      const char* lastsep = strrchr(file, '/');
      if (lastsep) {
        file = lastsep + 1;
      }
      printf("%s:%d: Check ", file, line);
    }
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("... ");
    _color_print(result_color, result_str);
    printf("\n");
    _current_unit_log_cnt++;
  }
  return cond;
}

#define TEST_CHECK_(cond, ...) \
  _test_check_((cond), __FILE__, __LINE__, __VA_ARGS__)
#define TEST_CHECK(cond) _test_check_((cond), __FILE__, __LINE__, "%s", #cond)

// 为 当前测试 case 添加注释
void _test_case_(const char* fmt, ...) {
  if (_opts.verbose_level < VerboseLevelDefault) {
    return;
  }
  if (_current_case_name[0]) {
    _current_case_log_cnt = 0;
    _current_case_name[0] = '\0';
  }
  if (!fmt) {
    return;
  }
  va_list args;
  va_start(args, fmt);
  vsnprintf(_current_case_name, sizeof(_current_case_name), fmt, args);
  va_end(args);
  if (_opts.verbose_level >= VerboseLevelVerbose) {
    _test_line_indent(1);
    _color_print(colors.normal_dark, "Case %s:\n", _current_case_name);
    _current_case_log_cnt++;
    _current_unit_log_cnt++;
  }
}

#define TEST_CASE_(...) _test_case_(__VA_ARGS__)
#define TEST_CASE(name) _test_case_("%s", name);

static void _test_pre_do_run(const Test* test, int index) {
  _current_test = test;
  _current_index = index;
  _current_unit_fail_cnt = 0;
  _current_unit_log_cnt = 0;
}
static void _test_post_do_run(const Test* test, int index) {
  _test_case_(NULL);
  _current_test = NULL;
}

// 直接调用执行单元测试用例函数
static bool _test_do_run(const Test* test, int index) {
  // 1) 当前测试用例全局变量设置
  _test_pre_do_run(test, index);
  // 2) 输出当前测试
  _test_begin_line(test);
  fflush(stdout);
  fflush(stderr);
  // 3)定时器启动
  _timer_start();
  // 4) 执行测试用例方法
  test->fun();
  _timer_stop();
  if (_current_unit_fail_cnt == 0) {
    if (_opts.verbose_level == VerboseLevelVerbose) {
      _color_print(colors.green_dark, "SUCCESS:");
      printf("所有断言都已经通过!");
      _test_line_indent(1);
      printf("执行用时:");
      _timer_print_ms();
      printf("\n");
    } else if (_opts.verbose_level > VerboseLevelSilent) {
      _test_end_line(0);
    }
  } else {
    if (_opts.verbose_level == VerboseLevelVerbose) {
      _color_print(colors.red_dark, "FAILED:");
      printf("%d 个断言失败.\n", _current_unit_fail_cnt);
    }
  }
  _test_post_do_run(test, index);
  return _current_unit_fail_cnt == 0;
}

// 创建子进程以执行单元测试,这样子进程的段错误等,不会影响主进程崩溃
static bool _test_exec_in_child_process(const Test* test, int index) {
  pid_t pid = fork();
  if (pid == -1) {
    _test_error("创建测试子进程失败. %s [%d] \n", strerror(errno), errno);
    return false;
  } else if (pid == 0) {
    // 子进程中
    bool success = _test_do_run(test, index);
    exit(success ? 0 : 1);
  } else {
    // 父进程,
    int exit_code;
    waitpid(pid, &exit_code, 0);
    if (WIFEXITED(exit_code)) {
      //子进程通过 exit 调用正常结束.
      switch (WEXITSTATUS(exit_code)) {
        case 0:
          return true;
        case 1:
          return false;
        default:
          _test_error("测试子进程未知的退出码 [%d]", WEXITSTATUS(exit_code));
      }
    } else if (WIFSIGNALED(exit_code)) {
      // 子进程因为接收到终止信号终止
      const char* signame = strsignal(WTERMSIG(exit_code));
      _test_error("测试子进程被信号 %s 中断.", signame);
    } else {
      _test_error("测试子进程意外退出 [%d]", exit_code);
    }
    return false;
  }
}

// 执行测试用例
static bool _test_run(const Test* test, int index) {
  bool success = true;
  if (_opts.no_exec) {
    success = _test_do_run(test, index);
  } else {
    success = _test_exec_in_child_process(test, index);
  }
  return success;
}

static const TestDetail _test_details[100] = {};

extern void run_tests(const Test tests[], const TestOptions* opts) {
  // 1) 复制选项
  if (opts) {
    _opts.no_exec = opts->no_exec;
    _opts.verbose_level = opts->verbose_level;
  }
  // 2) 重新包装 Test 对象
  for (int i = 0; tests[i].fun; i++) {
    _test_run(&tests[i], i);
  }
}