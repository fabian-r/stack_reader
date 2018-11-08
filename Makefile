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
