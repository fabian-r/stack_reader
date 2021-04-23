A small program that prints all accessible stack contents on a linux system.
Pretty useless by itself but nice to visualize what the run time environment
puts into the stack.

Have a look at the Makefile to see how to use it.

**Disclaimer:** The program is basically an intentional stack buffer overflow. This is undefined behavior, therefore your compiler *could* translate this program in **literally every way**, e.g. to erase your hard drive, set your PC on fire, make demons fly out of your nose, or order a pizza to your current location. Use it at your own risk. 
