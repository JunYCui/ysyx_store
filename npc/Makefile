TOPNAME = ysyxSoCFull
INC_PATH = $(NPC_HOME)/include 


VSOURCES=$(shell find $(abspath ./vsrc/CPU) -name "*.v" -or -name "*.sv" )
CSOURCES=$(shell find $(abspath ./csrc/cpu) -name "*.c" -or -name "*.cc" -or -name "*.cpp")

# add ysyxsoc
VSOURCES += $(shell find $(abspath ../ysyxSoC/perip) -name "*.v" )
VSOURCES += $(shell find $(abspath ../ysyxSoC/build) -name "*.v" )
INC_VDEFINE += /home/cjy/ysyx-workbench/ysyxSoC/perip/uart16550/rtl /home/cjy/ysyx-workbench/ysyxSoC/perip/spi/rtl
Warning = UNUSEDSIGNAL ASSIGNDLY DECLFILENAME PINCONNECTEMPTY DEFPARAM UNDRIVEN SYNCASYNCNET UNUSEDPARAM
VERILATOR_FLAGS += --timescale "1ns/1ns" --no-timing --autoflush

CONSTR = constr/$(TOPNAME).nxdc
BUILD_DIR = $(NPC_HOME)/build

SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@


CSOURCES += $(SRC_AUTO_BIND)

OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

DIFF_REF_SO = $(NEMU_HOME)/build/riscv32-nemu-interpreter-so
ARGS_DIFF = -d $(DIFF_REF_SO)

VERILATOR = verilator
# -- assert allows all assert -sv allows SV parses
VERILATOR_FLAGS += -Wall --cc -MMD --build --trace $(addprefix -Wno-, $(Warning)) --assert  \
			-O2 --x-assign fast --x-initial fast  $(addprefix -I, $(INC_VDEFINE))


LDFLAGS = -lSDL2 -lSDL2_image -O2 -lreadline -ldl -pie -g

include $(NVBOARD_HOME)/scripts/nvboard.mk


INCFLAGS = $(addprefix -I, $(INC_PATH))

CFLAGS  = -O2 -MMD -Wall -DTOP_NAME="\"V$(TOPNAME)\""  $(INCFLAGS) 

LDFLAGS += $(shell llvm-config --libs) -fsanitize=address 

CFLAGS += -I/usr/lib/llvm-14/include -std=c++14 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -fPIE -rdynamic

IMG ?= 

override ARGS += $(ARGS_DIFF)

$(shell mkdir -p $(BUILD_DIR))

NPC_EXEC = $(BIN) $(ARGS) $(IMG)


.PHONY:sim
sim:all
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self." 
	$(NPC_EXEC)

gdb: all
	$(call git_commit, "gdb NEMU")
	gdb -s $(BIN) --args $(NPC_EXEC)

.PHONY:all
all:$(CSOURCES) $(VSOURCES)  $(NVBOARD_ARCHIVE)
	@echo "Write this Makefile by your self."
	@rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME) \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))\





clean: 
	rm -rf $(BUILD_DIR) *.vcd
#waves:*.vcd
#	gtkwave *.vcd

#.PHONY:clean
#clean:
#	@rm -rf ./obj_dir *.vcd

include ../Makefile
