CSOURCES = char_test.c
CC = riscv64-linux-gnu-gcc
CFLAGS = -std=gnu11 -O2 -MMD -Wall -Werror -Wno-main \
		-march=rv32e_zicsr -mabi=ilp32e \
		-static

run:$(CSOURCES)
	$(CC) $(CFLAGS) $(CSOURCES) -c -o char_test.o