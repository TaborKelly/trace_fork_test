# trace fork test
## why?
Linux kernel tracing for `syscalls/sys_enter_fork` doesn't appear to work on 5.19.17.

On my Ubuntu 22.04 box:
```
$ uname -a
Linux framework0 5.19.17-051917-generic #202210240939 SMP PREEMPT_DYNAMIC Mon Oct 24 09:43:01 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
$ make && sudo ./forktest
gcc -o forktest main.c
I'm the fork() parent PID: 52991
I'm the fork() child
I'm the vfork() child
I'm the vfork() parent PID: 52992
# tracer: nop
#
# entries-in-buffer/entries-written: 2/2   #P:16
#
#                                _-----=> irqs-off/BH-disabled
#                               / _----=> need-resched
#                              | / _---=> hardirq/softirq
#                              || / _--=> preempt-depth
#                              ||| / _-=> migrate-disable
#                              |||| /     delay
#           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
#              | |         |   |||||     |         |
        forktest-52987   [002] ..... 17953.273284: sys_vfork()
              sh-52993   [002] ..... 17953.273776: sys_vfork()
```