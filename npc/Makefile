TOPNAME = switch
VERILATOR_FLAGS=--cc --exe --build --trace
VERILATOR_CSOURCES=$(PWD)/csrc/*.cpp
VERILATOR_VSOURCES=$(PWD)/vsrc/*.v
all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator $(VERILATOR_FLAGS) $(VERILATOR_CSOURCES) $(VERILATOR_VSOURCES)
	obj_dir/V$(TOPNAME)
include ../Makefile
