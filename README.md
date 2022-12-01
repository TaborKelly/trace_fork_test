# trace fork test
## TL;DR
libc calls `sys_clone()` not `sys_fork()`, for `fork()` at least sometimes one some systems.

## why?
Once upon a time I was just sitting at my desk trying to trace all of the `fork()` calls on my linux system. But I didn't see any. It only took me days to figure out that libc was calling `sys_clone()` instead of `sys_fork()`. This is here so that you don't have to go through that, hopefully.

```
$ uname -a
Linux framework0 6.0.10 #1 SMP PREEMPT_DYNAMIC Wed Nov 30 10:55:16 PST 2022 x86_64 x86_64 x86_64 GNU/Linux
$ make && sudo ./forktest
make: 'forktest' is up to date.
I'm the fork() parent, child PID: 20353
I'm the vfork() child
I'm the vfork() parent, child PID: 20354
I'm the fork() child
# tracer: nop
#
# entries-in-buffer/entries-written: 8/8   #P:16
#
#                                _-----=> irqs-off/BH-disabled
#                               / _----=> need-resched
#                              | / _---=> hardirq/softirq
#                              || / _--=> preempt-depth
#                              ||| / _-=> migrate-disable
#                              |||| /     delay
#           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
#              | |         |   |||||     |         |
        forktest-20346   [006] ..... 14890.324591: sys_clone(clone_flags: 1200011, newsp: 0, parent_tidptr: 0, child_tidptr: 7f873f2c5a10, tls: 0)
        forktest-20346   [006] ..... 14890.324642: sched_process_fork: comm=forktest pid=20346 child_comm=forktest child_pid=20353
        forktest-20346   [006] ..... 14890.324683: sys_vfork()
        forktest-20346   [006] ..... 14890.324693: sched_process_fork: comm=forktest pid=20346 child_comm=forktest child_pid=20354
        forktest-20346   [006] ..... 14890.324731: sys_clone3(uargs: 7ffc765d2090, size: 58)
        forktest-20346   [006] ..... 14890.324739: sched_process_fork: comm=forktest pid=20346 child_comm=forktest child_pid=20355
              sh-20355   [000] ..... 14890.325198: sys_vfork()
              sh-20355   [000] ..... 14890.325208: sched_process_fork: comm=sh pid=20355 child_comm=sh child_pid=20356
```
