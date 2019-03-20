NAME := test
CC := gcc
ASM := nasm -f elf64

all:
	$(ASM) enc.s -o enc.o
	$(ASM) dec.s -o dec.o
	$(CC) main.c enc.o dec.o -o $(NAME)

clean:
	rm -f enc.o
	rm -f dec.o

fclean: clean
	rm $(NAME)
