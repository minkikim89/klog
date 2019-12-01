#ifndef __KLOG_H__
#define __KLOG_H__

typedef enum kloglevel {
    KLOG_TRACE = 0,
    KLOG_DEBUG,
    KLOG_INFO,
    KLOG_WARN,
    KLOG_ERROR,
    KLOG_FATAL
} KLOGLEVEL;

int  klog_init(char *path);
void klog_log(unsigned int loglevel, const char *file, const char *func,
              int line, const char *fmt, ...);
void klog_set_loglevel(unsigned int loglevel);
void klog_set_max_file_size(unsigned int loglevel);
void klog_destroy(void);

#define klog(loglevel, ...) klog_log(loglevel, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_trace(...)     klog_log(KLOG_TRACE, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_debug(...)     klog_log(KLOG_DEBUG, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_info(...)      klog_log(KLOG_INFO, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_warn(...)      klog_log(KLOG_WARN, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_error(...)     klog_log(KLOG_ERROR, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define klog_fatal(...)     klog_log(KLOG_FATAL, __FILE__, __func__, __LINE__, __VA_ARGS__)
#endif
