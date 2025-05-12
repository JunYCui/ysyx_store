Module = ysyx_24100029_IFU
TOPNAME_TB = $(Module)_tb
INC_VDEFINE = $(NPC_HOME)/vsrc/CPU/define

BUILD_DIR = ./build
WAVE_DIR = ./wave
OBJ_DIR = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/$(Module)
VERILATOR=verilator

NPROC = $(shell nproc)

$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(WAVE_DIR))

VSOURCES = $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv" )
VSOURCES += $(shell find $(abspath ../npc) -name "*.v" -or -name "*.sv" )


CSOURCES = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
SINGLE_VSRC =  $(shell find $(abspath ../) -name "$(Module)*.v" -or -name "$(Module)*.sv" )


Warning = WIDTHTRUNC UNUSEDPARAM WIDTHEXPAND UNUSEDSIGNAL DECLFILENAME EOFNEWLINE


CFLAGS  = -O2 -MMD -Wall $(INCFLAGS)

VERILATOR_FLAGS += -Wall --cc -MMD  --trace --assert  --timing --timescale-override 1ns/100ps $(addprefix -Wno-, $(Warning)) \
			-O2 --x-assign fast --x-initial fast $(addprefix -I, $(INC_VDEFINE)) --prefix "VSimTop"

VERILATOR_FLAGS += --threads 4 --threads-dpi pure 

all:$(CSOURCES) $(VSOURCES)
	rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME_TB)  \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

single_sim:$(CSOURCES) $(SINGLE_VSRC)
	rm -rf $(OBJ_DIR) *.vcd
	$(VERILATOR) $(VERILATOR_FLAGS) \
	--top-module $(TOPNAME_TB) \
	$(addprefix -CFLAGS , $(CFLAGS))  $(addprefix -LDFLAGS , $(LDFLAGS)) \
	$^ \
	--Mdir $(OBJ_DIR)  --exe -o $(abspath $(BIN))

single_run:single_sim
	$(BIN)

run:all
	make -C $(OBJ_DIR) -j$(nproc) -f VSimTop.mk 
	$(BIN)

clean:
	@rm -rf ./build/* \
	@rm -rf ./wave/*

wav:
	gtkwave wave/waveform.vcd


.PHONY: wav clean run all