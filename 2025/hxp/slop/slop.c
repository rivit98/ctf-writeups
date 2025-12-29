#define _GNU_SOURCE
#include <err.h>
#include <errno.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/prctl.h>
#include <linux/seccomp.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/random.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

static struct sock_filter bpf_filter[] = {
    /* Check the architecture */
    /* 00 */ BPF_STMT(BPF_LD  | BPF_ABS | BPF_W, (offsetof(struct seccomp_data, arch))),
    /* 01 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 1, 0),
    /* 02 */ BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
    /* Check allowed system calls */
    /* 03 */ BPF_STMT(BPF_LD  | BPF_ABS | BPF_W, (offsetof(struct seccomp_data, nr))),
    /* 04 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_pause,      12, 0),
    /* 05 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_nanosleep,  11, 0),
    /* 06 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_alarm,      10, 0),
    /* 07 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_getpid,      9, 0),
    /* 08 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit,        8, 0),
    /* 09 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_wait4,       7, 0),
    /* 10 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_kill,        6, 0),
    /* 11 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_getcwd,      5, 0),
    /* 12 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_sysinfo,     4, 0),
    /* 13 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_tkill,       3, 0),
    /* 14 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit_group,  2, 0),
    /* 15 */ BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_waitid,      1, 0),
    /* 16 */ BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
    /* 17 */ BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
};

void *handle_request(void *arg)
{
    register int conn = (int) (intptr_t) arg;

    static const char *prompt = "send me your slop:\n";
    if (write(conn, prompt, strlen(prompt)) != (ssize_t) strlen(prompt)) {
        warn("failed to send prompt");
        return NULL;
    }

    if (read(conn, __builtin_frame_address(0), 0x300) < 0) {
        warn("failed to read input");
        return NULL;
    }

    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0))
        err(EXIT_FAILURE, "failed to set no-new-privileges mode");

    struct sock_fprog filter = {
        .len = sizeof(bpf_filter) / sizeof(bpf_filter[0]),
        .filter = bpf_filter
    };

    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &filter, 0, 0))
        err(EXIT_FAILURE, "failed to install seccomp filter");

    return NULL;
}

__attribute__((zero_call_used_regs("all")))
uintptr_t random_memory(void)
{
    /* sad hlt noises... no messing with my stack */
    void *random = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (random == MAP_FAILED)
        err(EXIT_FAILURE, "failed to map 'secure' memory");
    register uintptr_t stack = 0;
    do {
        ssize_t space = getrandom(random, 0x1000, 0);
        if (space < 0)
            err(EXIT_FAILURE, "failed to randomize stack address");
        for (size_t offset = 0; offset + 8 <= (size_t) space; ++offset) {
            register uintptr_t address = * (uintptr_t *) (((char *) random) + offset) & 0x7ffffffff000ul;
            if (address < 0x10000)
                continue;
            if (mmap((void *) address, 0x8000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) == MAP_FAILED) {
                if (errno != EEXIST)
                    err(EXIT_FAILURE, "failed to map stack");
                continue;
            }
            stack = address + 0x4008;
            break;
        }
    } while (0);
    if (munmap(random, 0x1000))
        err(EXIT_FAILURE, "failed to unmap 'secure' memory");
    return stack;
}


int main(void)
{
    setbuf(stdout, NULL);

    int so = socket(AF_INET6, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    if (so < 0)
        err(EXIT_FAILURE, "failed to create socket");

    const int one = 1;
    if (setsockopt(so, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)))
        err(EXIT_FAILURE, "failed to set SO_REUSEADDR");

    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(1024);
    if (bind(so, (const struct sockaddr *) &addr, sizeof(addr)) < 0)
        err(EXIT_FAILURE, "failed to bind socket");

    if (listen(so, 16))
        err(EXIT_FAILURE, "failed to listen on socket");

    int conn = accept4(so, NULL, NULL, SOCK_CLOEXEC);
    if (conn < 0)
        err(EXIT_FAILURE, "failed to accept connection");

    register uintptr_t new_stack = random_memory();

    pthread_t thread;
    pthread_attr_t attr;
    int error;
    if ((error = pthread_attr_init(&attr)))
        errx(EXIT_FAILURE, "failed to initialize thread attributes: %s", strerror(error));
    if ((error = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)))
        errx(EXIT_FAILURE, "failed to initialize thread attributes: %s", strerror(error));
    if ((error = pthread_create(&thread, &attr, handle_request, (void *) (intptr_t) conn)))
        errx(EXIT_FAILURE, "failed to spawn thread: %s", strerror(error));

    __asm__ volatile (
        "movq %[stack], %%rsp\n"
        "1:\n"
        "movl %[sched_yield], %%eax\n"
        "syscall\n"
        "jmp 1b\n"
        :: [stack]"r"(new_stack),
           [sched_yield]"i"(__NR_sched_yield)
    );
    __builtin_unreachable();
}
