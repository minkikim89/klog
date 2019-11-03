#include <stdio.h>
#include "klog.h"

int main()
{
  /* console logger initialize */
  klog_init(NULL); // NULL parameter means console print

  klog_set_loglevel(KLOG_WARN);
  klog_debug("Console log print DEBUG. It will be not printed");
  klog_warn("Console log print WARN.");
  klog(KLOG_ERROR, "It is another way to print ERROR log.");
  klog_destroy();

  klog_init("./log");
  // if do not set log level, default level is KLOG_INFO
  klog_info("File log print INFO.");
  klog_error("File log print ERROR.");
  klog_destroy();
  return 0;
}
