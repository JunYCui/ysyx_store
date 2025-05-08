Module = ysyx_24100029_IFU
TOPNAME_TB = $(Module)_tb
INC_VDEFINE = $(NPC_HOME)/vsrc/CPU/define 

BUILD_DIR = ./build
WAVE_DIR = ./wave
OBJ_DIR = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/$(Module)
VERILATOR=verilator

$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(WAVE_DIR))

VSOURCES = $(shell find $(abspath ../) -name "*.v" -or -name "*.sv" )
CSOURCES = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
SINGLE_VSRC =  $(shell find $(abspath ../) -name "$(Module)*.v" -or -name "$(Module)*.sv" )


Warning = WIDTHTRUNC UNUSEDPARAM WIDTHEXPAND UNUSEDSIGNAL DECLFILENAME


CFLAGS  = -O2 -MMD -Wall $(INCFLAGS) -DVtop="\"V$(TOPNAME_TB)\""

VERILATOR_FLAGS += -Wall --cc -MMD --build --trace --assert  --timing --timescale-override 1ns/100ps $(addprefix -Wno-, $(Warning)) \
			-O2 --x-assign fast --x-initial fast $(addprefix -I, $(INC_VDEFINE))

all:$(CSOURCES) $(VSOURCES)
	sed -i.bak 's/^#include[[:space:]]*[<\"]V.\+\.h[>\"]/#include"V$(TOPNAME_TB).h"/' $< 
	rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME_TB) \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))

single_sim:$(CSOURCES) $(SINGLE_VSRC)
	sed -i.bak 's/^#include[[:space:]]*[<\"]V.\+\.h[>\"]/#include"V$(TOPNAME_TB).h"/' $< 
	rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME_TB) \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))

single_run:single_sim
	$(BIN)

run:all
	$(BIN)

clean:
	@rm -rf ./build/* \
	@rm -rf ./wave/*

wav:
	gtkwave wave/waveform.vcd


.PHONY: wav clean run all