TOPNAME = top
SUBNAME = ps2_keyboard
SUBNAME+ = seg7 
#VERILATOR_trace_FLAGS=--cc --exe --build --trace

CSOURCES=$(shell find $(abspath ./vsrc) -name "$(TOPNAME).v" -or -name "$(SUBNAME).v" )
VSOURCES=$(shell find $(abspath ./csrc) -name "$(TOPNAME).c" -or -name "$(TOPNAME).cc" -or -name "$(TOPNAME).cpp")

SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
CSOURCES += $(SRC_AUTO_BIND)
CONSTR = constrain/$(TOPNAME).nxdc

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
INC_PATH ?=

#传递给verilator的参数：以c++形式输出调试信息，并自动依据makefile进行构建
VERILATOR_CFLAGS += -Wall --cc -MMD --build \
			-O3 --x-assign fast --x-initial fast --noassert 

#传递给preproject连接器的信息，添加SDL2库信息
LDFLAGS += -lSDL2 -lSDL2_image

include $(NVBOARD_HOME)/scripts/nvboard.mk
#包含文件路径，加前缀-I传递给g++，INC_PATH在nvbroad.mk中定义
INCFLAGS = $(addprefix -I, $(INC_PATH))

#传递给g++的编译参数，包括包含路径和TOP_NAME的定义
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
#新建构建目录，防止出现无法新建autobind.cpp的错误
$(shell mkdir -p $(BUILD_DIR))

.PHONY:all
all:
	@echo "Write this Makefile by your self."

.PHONY:sim
sim:  $(CSOURCES) $(VSOURCES) $(NVBOARD_ARCHIVE) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	@rm -rf $(OBJ_DIR)
	verilator $(VERILATOR_CFLAGS) \
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
