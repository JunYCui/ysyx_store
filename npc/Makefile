#get platform
ARCH_SPLIT = $(subst -, ,$(ARCH))
PLATFORM   = $(word 2,$(ARCH_SPLIT))

#define TOPNAME
ifeq ($(PLATFORM),ysyxsoc)
TOPNAME = ysyxSoCFull
else ifeq ($(PLATFORM),npc)
TOPNAME = ysyx_24100029
endif
INC_PATH = $(NPC_HOME)/include 
#add vsrc and csrc
VSOURCES=$(shell find $(abspath ./vsrc/CPU) -name "*.v" -or -name "*.sv" )
CSOURCES=$(shell find $(abspath ./csrc/cpu) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
INC_VDEFINE = $(NPC_HOME)/vsrc/CPU/define

# add ysyxsoc
ifeq ($(PLATFORM),ysyxsoc)
VSOURCES += $(shell find $(abspath ../ysyxSoC/perip) -name "*.v" )
VSOURCES += $(shell find $(abspath ../ysyxSoC/build) -name "*.v" )
INC_VDEFINE += /home/cjy/ysyx-workbench/ysyxSoC/perip/uart16550/rtl /home/cjy/ysyx-workbench/ysyxSoC/perip/spi/rtl
CONSTR = constr/$(TOPNAME).nxdc

SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(CONSTR)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

CSOURCES += $(SRC_AUTO_BIND)

endif

#build directory
BUILD_DIR = $(NPC_HOME)/build
$(shell mkdir -p $(BUILD_DIR))
# lint off warning
Warning = UNUSEDSIGNAL ASSIGNDLY DECLFILENAME PINCONNECTEMPTY DEFPARAM UNDRIVEN SYNCASYNCNET UNUSEDPARAM
VERILATOR_FLAGS += --timescale "1ns/1ns" --no-timing --autoflush

ifeq ($(PLATFORM),npc)
VERILATOR_FLAGS += -GResetValue=0x80000000 -DNPC
VSOURCES=$(shell find $(abspath ./vsrc/SRAM) -name "*.v" -or -name "*.sv" )
endif

OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

DIFF_REF_SO = $(NEMU_HOME)/build/riscv32-nemu-interpreter-so
ARGS_DIFF = -d $(DIFF_REF_SO)

VERILATOR = verilator
# -- assert allows all assert -sv allows SV parses
VERILATOR_FLAGS += -Wall --cc -MMD --build --trace $(addprefix -Wno-, $(Warning)) --assert  \
			-O2 --x-assign fast --x-initial fast  $(addprefix -I, $(INC_VDEFINE))


LDFLAGS = -lSDL2 -lSDL2_image -O2 -lreadline -ldl -pie 


INCFLAGS = $(addprefix -I, $(INC_PATH))

CFLAGS  = -O2 -MMD -Wall $(INCFLAGS) -D__$(shell echo $(PLATFORM) | tr a-z A-Z)__ -DTOP_NAME="\"V$(TOPNAME)\""

LDFLAGS += $(shell llvm-config --libs) -fsanitize=address 

CFLAGS += -I/usr/lib/llvm-14/include -std=c++14 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -fPIE -rdynamic

IMG ?= 

override ARGS += $(ARGS_DIFF)

NPC_EXEC = $(BIN) $(ARGS) $(IMG)

ifeq ($(PLATFORM),ysyxsoc)
include $(NVBOARD_HOME)/scripts/nvboard.mk
endif
NVBOARD_ARCHIVE ?= 

sim:all
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(NPC_EXEC)

gdb: all
	$(call git_commit, "gdb NEMU")
	gdb -s $(BIN) --args $(NPC_EXEC)

all:$(CSOURCES) $(VSOURCES)  $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME) \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))\



clean: 
	rm -rf $(BUILD_DIR) *.vcd

area:
	@sed -i '/Performance/d' ./vsrc/CPU/define/para.v
	@echo "analyse the chip area and frequency"
	@$(MAKE) -C ~/yosys-sta sta > log.txt 
	@grep --after-context=1 "Chip area" log.txt > area.txt
	@grep --after-context=7 "Endpoint" log.txt > frequency.txt 
	@sed -i '$$a \`define Performance_Count' ./vsrc/CPU/define/para.v

perf:
	@sed -i '/Performance/d' ./vsrc/CPU/define/para.v
	@echo "analyse the chip area and frequency"
	@$(MAKE) -C ~/yosys-sta sta > log.txt 
	@grep --after-context=1 "Chip area for top module " log.txt > area.txt
	@grep --after-context=7 "Endpoint" log.txt > frequency.txt 
	@sed -i '$$a \`define Performance_Count' ./vsrc/CPU/define/para.v
	@echo "microbench test"
	@$(MAKE) -C ../am-kernels/benchmarks/microbench ARCH=riscv32e-ysyxsoc mainargs=train run > log1.txt
	@grep --after-context=9 "total_count" log1.txt > count.txt
.PHONY: clean all sim perf area
#waves:*.vcd
#	gtkwave *.vcd

#.PHONY:clean
#clean:
#	@rm -rf ./obj_dir *.vcd
include ../Makefile
