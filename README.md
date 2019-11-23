# klog
klog is a simple logger for c language.

# Screenshot
- Console log mode

<img width="750" alt="screenshot_console" src="https://user-images.githubusercontent.com/12155982/68599410-da9c8700-04e3-11ea-9d1c-504fc5d661e7.png">

- File log mode

<img width="850" alt="screenshot_file" src="https://user-images.githubusercontent.com/12155982/68599412-dcfee100-04e3-11ea-9757-78c479b12545.png">

# Level
TRACE, DEBUG, INFO(default), WARN, ERROR, FATAL

# Feature
- Thread-safe
- Color print
- Logs to console, file

# usage
Copy klog.c, klog.h files and compile with your project.

If you want to use console log, use NULL parameter.
```c
klog_init(NULL);
klog_set_loglevel(KLOG_TRACE);
klog_trace("Hi!");
klog_debug("This is a simple log library.");
klog_info("It is very lightweight and easy to use.");
klog_warn("You can print logs to a console or a file.");
klog_error("Try out.");
klog_fatal(":-)");
```

If you want to use file log, pass a file path as a parameter
```c
klog_init("./log");
klog_set_loglevel(KLOG_TRACE);
klog_info("This is info log.");
klog_warn("This is warn log.");
```

See the code [sample_code.c](sample_code.c) for more details.
