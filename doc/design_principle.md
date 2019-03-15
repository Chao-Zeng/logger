
# design principle
1. only two interface
```c++
    void init_logger();
    void write_log();
```

2. interface shouldn't block caller and return immediately.

3. logger is scalable and easy to extend.

# logger implementation layers

| interface layer |
|:---------------:|
| filter layer    |
| core layer      |
| formatter layer |
| writer layer    |

1. interface layer

    logger interface to caller

2. filter layer

    filter log record, only pass need write record to core layer.

3. core layer

    core will collect log record and combine other components.

4. formatter layer

    format a log record to a standard log line message

5. writer layer
    write standard log line message to concrete file. Such as console, file, android ADT or Xcode.