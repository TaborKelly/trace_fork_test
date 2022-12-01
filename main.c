#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

char tracing_root[] = "/sys/kernel/debug/tracing";

int main(int argc, char *argv[])
{
    size_t buff_size = 1024;
    char buff[buff_size];

    snprintf(buff, buff_size, "echo 1 > %s/events/syscalls/sys_enter_fork/enable", tracing_root);
    int r = system(buff);
    assert(r == 0);

    snprintf(buff, buff_size, "echo 1 > %s/events/syscalls/sys_enter_vfork/enable", tracing_root);
    r = system(buff);
    assert(r == 0);

    snprintf(buff, buff_size, "echo 1 > %s/events/syscalls/sys_enter_clone/enable", tracing_root);
    r = system(buff);
    assert(r == 0);

    snprintf(buff, buff_size, "echo 1 > %s/events/syscalls/sys_enter_clone3/enable", tracing_root);
    r = system(buff);
    assert(r == 0);

    snprintf(buff, buff_size, "echo 1 > %s/events/sched/sched_process_fork/enable", tracing_root);
    r = system(buff);
    assert(r == 0);

    snprintf(buff, buff_size, "echo > %s/trace", tracing_root);
    r = system(buff);
    assert(r == 0);

    pid_t pid = fork();
    assert(pid >= 0);
    if(pid == 0) {
        printf("I'm the fork() child\n");
        exit(0);
    } else {
        printf("I'm the fork() parent, child PID: %d\n", pid);
    }

    pid = vfork();
    assert(pid >= 0);
    if(pid == 0) {
        printf("I'm the vfork() child\n");
        _exit(0);
    } else {
        printf("I'm the vfork() parent, child PID: %d\n", pid);
    }

    snprintf(buff, buff_size, "cat %s/trace", tracing_root);
    r = system(buff);
    assert(r == 0);

    return 0;
}
