TOPNAME = ALU
#VERILATOR_trace_FLAGS=--cc --exe --build --trace

VSOURCES=$(shell find $(abspath ./vsrc) -name "*.v" )
CSOURCES=$(shell find $(abspath ./csrc) -name "$(TOPNAME).c" -or -name "$(TOPNAME).cc" -or -name "$(TOPNAME).cpp")


SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
CSOURCES += $(SRC_AUTO_BIND)
CONSTR = constrain/$(TOPNAME).nxdc

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

VERILATOR = verilator

VERILATOR_CFLAGS += -Wall --cc -MMD --build \
			-O3 --x-assign fast --x-initial fast --noassert 

LDFLAGS += -lSDL2 -lSDL2_image

include $(NVBOARD_HOME)/scripts/nvboard.mk

INCFLAGS = $(addprefix -I, $(INC_PATH))

CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(shell mkdir -p $(BUILD_DIR))

.PHONY:all
all:
	@echo "Write this Makefile by your self."
	make sim
	$(BUILD_DIR)/$(TOPNAME)

.PHONY:sim
sim:  $(CSOURCES) $(VSOURCES) $(NVBOARD_ARCHIVE) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) \
		$^ \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		$(addprefix -CFLAGS , $(CFLAGS)) \
		--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))\
		

#waves:*.vcd
#	gtkwave *.vcd

#.PHONY:clean
#clean:
#	@rm -rf ./obj_dir *.vcd

$(SRC_AUTO_BIND): $(CONSTR) 
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py  $^ $@

include ../Makefile
