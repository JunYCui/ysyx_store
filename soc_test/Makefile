CSOURCES = char_test.c
CC = riscv64-linux-gnu-gcc
CFLAGS = -std=gnu11 -O2 -MMD -Wall -Werror -Wno-main \
		-fvisibility=hidden -fno-pic -march=rv64g -mcmodel=medany -mstrict-align -march=rv32e_zicsr -mabi=ilp32e \
		-static

run:$(CSOURCES)
	$(CC) $(CFLAGS) $(CSOURCES) -c -o char_test.o