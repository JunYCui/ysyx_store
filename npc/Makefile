TOPNAME = switch
VERILATOR_FLAGS=--cc --exe --build --trace
VERILATOR_CSOURCES=$(PWD)/*.cpp
VERILATOR_VSOURCES=$(PWD)/*.v
all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator $(VERILATOR_FLAGS) $(VERILATOR_CSOURCES) $(VERILATOR_VSOURCES)
	
include ../Makefile
