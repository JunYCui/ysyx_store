AM_SRCS := riscv/ysyxsoc/start.S \
           riscv/ysyxsoc/trm.c \
		   riscv/ysyxsoc/cte.c \
		   riscv/ysyxsoc/ioe.c \
           riscv/ysyxsoc/timer.c \
		   riscv/ysyxsoc/id.S \
           riscv/ysyxsoc/trap.S 

CFLAGS    += -fdata-sections -ffunction-sections -O2
LDFLAGS   += -T $(AM_HOME)/scripts/ysyxsoclinker.ld  --print-map
LDFLAGS   += --gc-sections -e _start
CFLAGS += -DMAINARGS=\"$(mainargs)\" 
SOCFLAGS = -e $(IMAGE).elf -b


.PHONY: $(AM_HOME)/am/src/riscv/ysyxsoc/trm.c

image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

run: image
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) sim ARGS="$(SOCFLAGS)" IMG=$(IMAGE).bin

gdb: image
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) gdb ARGS="$(SOCFLAGS)" IMG=$(IMAGE).bin