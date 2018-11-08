// stack_reader, a small program to print stack contents
// Copyright 2018 Fabian Ritter
//
// Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
// Fabian Ritter wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer or coffee in return

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

