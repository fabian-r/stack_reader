#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
    fprintf(stderr, "\nCaught segfault at address %p, terminating...\n", si->si_addr);
    exit(0);
}

void install_segfault_handler(void) {
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
}

