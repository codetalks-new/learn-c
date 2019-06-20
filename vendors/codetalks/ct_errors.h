#pragma once
#include <errno.h>       /* for errno */
#include <stdarg.h>      /* for va_list */
#include <stdbool.h>     /* for bool,true,false */
#include <stdio.h>       /* for printf etc */
#include <stdlib.h>      /* abort,exit etc */
#include <stdnoreturn.h> /* for noreturn */
#include <string.h>      /* for strerror etc */
#include <unistd.h>

static void ct_terminate(bool force) {
  char* dump_core = getenv("EF_DUMP_CORE");
  if (dump_core != NULL && *dump_core != '\0') {
    abort();
  } else {
    if (force) {
      _exit(EXIT_FAILURE);
    } else {
      exit(EXIT_FAILURE);
    }
  }
}
typedef struct PrintErrorArgs {
  bool use_err;       /*是否使用错误码  */
  int err;            /*错误码 */
  bool flush_stdout;  /*是否刷新标准输出 */
  const char* format; /*自定义错误信息格式 */
  va_list ap;         /*用于错误信息的不定参数列表 */
} PrintErrorArgs;

static void ct_print_error(PrintErrorArgs* args, va_list ap) {
#define BUF_SIZE 512
  char buf[BUF_SIZE], user_msg[BUF_SIZE], err_text[BUF_SIZE];
  vsnprintf(user_msg, BUF_SIZE, args->format, ap);
  if (args->use_err) {
    snprintf(err_text, BUF_SIZE, "[%s]", strerror(args->err));
  } else {
    snprintf(err_text, BUF_SIZE, ":");
  }
  snprintf(buf, BUF_SIZE, "ERROR%s %s\n", err_text, user_msg);
  if (args->flush_stdout) {
    fflush(stdout);
  }
  fputs(buf, stderr);
  fflush(stderr);  // 如果 stderr 不是行缓冲模式则必需
}

void ct_log_error(const char* format, ...) {
  va_list ap;
  int errorno = errno;
  va_start(ap, format);
  PrintErrorArgs pe_args = {
      .use_err = true,
      .err = errno,
      .flush_stdout = true,
      .format = format,
  };
  ct_print_error(&pe_args, ap);
  va_end(ap);
  errno = errorno;
}

void ct_exit(const char* format, ...) {
  va_list ap;
  int errorno = errno;
  va_start(ap, format);
  PrintErrorArgs pe_args = {
      .use_err = true,
      .err = errno,
      .flush_stdout = true,
      .format = format,
  };
  ct_print_error(&pe_args, ap);
  va_end(ap);
  errno = errorno;
  ct_terminate(/*force*/ false);
}

void ct_force_exit(const char* format, ...) {
  va_list ap;
  int errorno = errno;
  va_start(ap, format);
  PrintErrorArgs pe_args = {
      .use_err = true,
      .err = errno,
      .flush_stdout = false,
      .format = format,
  };
  ct_print_error(&pe_args, ap);
  va_end(ap);
  errno = errorno;
  ct_terminate(/*force*/ true);
}

void ct_exit_en(int errnum, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  PrintErrorArgs pe_args = {
      .use_err = true,
      .err = errnum,
      .flush_stdout = true,
      .format = format,
  };
  ct_print_error(&pe_args, ap);
  va_end(ap);
  ct_terminate(/*force*/ false);
}

void ct_fatal(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  PrintErrorArgs pe_args = {
      .use_err = false,
      .err = 0,
      .flush_stdout = true,
      .format = format,
  };
  ct_print_error(&pe_args, ap);
  va_end(ap);
  ct_terminate(/*force*/ false);
}

void ct_usage_err(const char* format, ...) {
  va_list ap;
  fflush(stdout);
  fprintf(stderr, "Usage:");
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fflush(stderr);
  exit(EXIT_FAILURE);
}

void ct_cmdline_err(const char* format, ...) {
  va_list ap;
  fflush(stdout);
  fprintf(stderr, "Command-Line usage error:");
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fflush(stderr);
  exit(EXIT_FAILURE);
}