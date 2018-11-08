# stack_reader, a small program to print stack contents
# Copyright 2018 Fabian Ritter
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Fabian Ritter wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer or coffee in return

.PHONY: all clean zip

all: stack_reader

stack_reader: stack_reader.c handler.c
	gcc -O0 -o $@ $?

clean:
	rm stack_reader
	rm stack_reader.tgz

stack_reader.tgz: stack_reader.c handler.c Makefile
	tar -czvf $@ $?

zip: stack_reader.tgz

# Disables address space layout randomization, requires root, possibly
# unnecessary
disable_aslr:
	sysctl -w kernel.randomize_va_space=0

# Runs the stack_reader with an empty environment, except for the FOO variable,
# which is taken from the outside environment
# Call this as `FOO=bar make run` to set the FOO variable inside.
run: stack_reader
	env -i bash -c "FOO=$(FOO) ./stack_reader"
