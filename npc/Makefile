TOPNAME = cpu_v1
#VERILATOR_trace_FLAGS=--cc --exe --build --trace

VSOURCES=$(shell find $(abspath ./vsrc) -name "*.v" )
CSOURCES=$(shell find $(abspath ./csrc) -name "$(TOPNAME).c" -or -name "$(TOPNAME).cc" -or -name "$(TOPNAME).cpp")


SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
#CSOURCES += $(SRC_AUTO_BIND)
CONSTR = constrain/$(TOPNAME).nxdc

BUILD_DIR = $(NPC_HOME)/build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

VERILATOR = verilator

VERILATOR_CFLAGS += -Wall --cc -MMD --build --trace\
			-O3 --x-assign fast --x-initial fast --noassert 

LDFLAGS += -lSDL2 -lSDL2_image

include $(NVBOARD_HOME)/scripts/nvboard.mk

INCFLAGS = $(addprefix -I, $(INC_PATH))

CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

IMG ?=
$(shell mkdir -p $(BUILD_DIR))

NPC_EXEC = $()


.PHONY:sim
sim:all
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self." 
	$(NPC_HOME)/build/$(TOPNAME)

.PHONY:all
all:$(CSOURCES) $(VSOURCES) 
	@echo "Write this Makefile by your self."
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
	--top-module $(TOPNAME) \
		$^ \
		--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))\

#$(addprefix -LDFLAGS , $(LDFLAGS)) 
#$(addprefix -CFLAGS , $(CFLAGS)) 

clean: 
	rm -rf $(BUILD_DIR) *.vcd
#waves:*.vcd
#	gtkwave *.vcd

#.PHONY:clean
#clean:
#	@rm -rf ./obj_dir *.vcd

$(SRC_AUTO_BIND): $(CONSTR) 
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py  $^ $@

include ../Makefile
