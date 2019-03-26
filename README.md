# logger
logger is a scalable and light weighted linux server async log component.

# design principle
1. simple interface, header only

2. async

3. scalable

# logger implementation layers

| layers          |
|:---------------:|
| interface layer |
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
    write standard log line message to concrete file.
