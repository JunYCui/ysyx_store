TOPNAME = switch
VERILATOR_FLAGS=--cc --exe --build --trace
VERILATOR_CSOURCES=$(PWD)/csrc/*.cpp
VERILATOR_VSOURCES=$(PWD)/vsrc/*.v


all:
	@echo "Write this Makefile by your self."
.PHONY:sim
sim:   
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator $(VERILATOR_FLAGS) $(VERILATOR_CSOURCES) $(VERILATOR_VSOURCES)
	obj_dir/V$(TOPNAME)
waves:*.vcd
	gtkwave *.vcd
.PHONY:clean
clean:
	@rm -rf ./obj_dir *.vcd

include ../Makefile
