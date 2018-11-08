#include <stdio.h>
#include <stdint.h>

#define WIDTH 32

void install_segfault_handler(void);

void printStack(void) {
    char local = '*';
    char* stack_pos = &local;

    uintptr_t stack_pos_int = (uintptr_t)stack_pos;

    stack_pos = (char*)(stack_pos_int - stack_pos_int % WIDTH);

    fprintf(stderr, "stack dump:\n");
    while (1) {
        char buf[WIDTH];
        for (int i = 0; i < WIDTH; ++i) {
            buf[i] = *(stack_pos++);
        }

        int chars_written = 0;
        fprintf(stderr, "%p%n |", stack_pos, &chars_written);
        for (int i = 0; i < WIDTH; ++i) {
            fprintf(stderr, " %02hhX", buf[i]);
        }
        fprintf(stderr, "\n");
        for (int i = 0; i < chars_written; ++i) {
            fprintf(stderr, " ");
        }
        fprintf(stderr, " |");
        for (int i = 0; i < WIDTH; ++i) {
            if (buf[i] >= 32 && buf[i] <= 126) {
                fprintf(stderr, "  %c", buf[i]);
            } else {
                fprintf(stderr, "   ", buf[i]);
            }
        }
        fprintf(stderr, "\n");
    }
}

int main(int argc, char *argv[]) {
    install_segfault_handler();
    char buf[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' };

    printStack();

    return 0;
}
