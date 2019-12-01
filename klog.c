#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "klog.h"

static FILE      *fp;
static KLOGLEVEL  global_loglevel;
static pthread_mutex_t global_log_lock;
static char      *global_file_path;

static unsigned int max_file_size;
static unsigned int now_file_size;
static unsigned int now_file_num;
static bool       console_log;

static const char *klog_level_str[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *klog_level_color[] = {
  "\x1B[0;90m", "\x1B[0;36m", "\x1B[0;32m", "\x1B[0;33m", "\x1B[0;31m", "\x1B[0;35m"
};

int klog_init(char *file_path)
{
  global_loglevel = KLOG_INFO;
  if (pthread_mutex_init(&global_log_lock, NULL) != 0) {
    return -1;
  }
  if (file_path == NULL) {
    console_log = true;
  } else {
    console_log = false;
    fp = fopen(file_path, "a");
    if (fp == NULL) {
      return -1;
    }
    global_file_path = strdup(file_path);
    //max_file_size = 128 * 1024 * 1024;
    max_file_size = 150;
  }
  return 0;
}

void klog_destroy(void)
{
  if (fp)
    fclose(fp);
}

void klog_set_loglevel(unsigned int loglevel)
{
  global_loglevel = loglevel;
}

void klog_set_max_file_size(unsigned int max_size)
{
  max_file_size = max_size;
}

void klog_log(unsigned int loglevel, const char *file, const char *func,
              int line, const char *fmt, ...)
{
  if (loglevel < global_loglevel) {
    return;
  }

  time_t t = time(NULL);
  struct tm lt;
  localtime_r(&t, &lt);
  va_list strs;
  va_start(strs, fmt);

  pthread_mutex_lock(&global_log_lock);
  if (console_log) {
    printf("%02d:%02d:%02d " // TIME
           "%s:%d(%s) "      // CODE LINE
           "%s%s:\x1B[0m ",  // LOG LEVEL
           lt.tm_hour, lt.tm_min, lt.tm_sec,
           file, line, func,
           klog_level_color[loglevel], klog_level_str[loglevel]);
    printf(fmt, strs);
    printf("\n");
    fflush(stdout);
  } else {
    now_file_size +=
    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] " // TIME
                "%s:%d(%s) "                       // CODE
                "%s: ",                            // LOG LEVEL
                lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday,
                lt.tm_hour, lt.tm_min, lt.tm_sec,
                file, line, func,
                klog_level_str[loglevel]);
    now_file_size +=
    vfprintf(fp, fmt, strs);
    now_file_size +=
    fprintf(fp, "\n");

    if (now_file_size >= max_file_size) {
      now_file_num = now_file_num % 5;
      char *new_file_path = malloc(strlen(global_file_path)+3);
      sprintf(new_file_path, "%s.%d", global_file_path, now_file_num);
      close(fp);
      rename(global_file_path, new_file_path);
      now_file_num++;

      fp = fopen(global_file_path, "w");
      if (fp == NULL) {
        //TODO rename, fopen error handling
      }
      now_file_size = 0;
    }
    fflush(fp);
  }
  pthread_mutex_unlock(&global_log_lock);
  va_end(strs);
}
