# trace fork test
## why?
Linux kernel tracing for `syscalls/sys_enter_fork` doesn't appear to work on kernel 6.0.10 built from [kernel.org](https://www.kernel.org/).

On my Ubuntu 22.04 box:
```
$ uname -a
Linux framework0 6.0.10 #1 SMP PREEMPT_DYNAMIC Wed Nov 30 10:55:16 PST 2022 x86_64 x86_64 x86_64 GNU/Linux
$ make && sudo ./forktest
make: 'forktest' is up to date.
I'm the fork() parent PID: 2808
I'm the fork() child
I'm the vfork() child
I'm the vfork() parent PID: 2809
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
        forktest-2804    [007] .....   116.068061: sys_vfork()
              sh-2810    [000] .....   116.068581: sys_vfork()
```

So `sys_vfork()` shows up in the trace but not `sys_fork()`.

## kernels
The above was built from [linux-6.0.10.tar.xz](https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.0.10.tar.xz). Other kernels that also exhibit this are `6.0.9-060009-generic` and `5.19.17-051917-generic` from https://kernel.ubuntu.com/~kernel-ppa/mainline/.

## Bugzilla
After mostly convincing myself that I wasn't going mad I filed a bug here: https://bugzilla.kernel.org/show_bug.cgi?id=216758
