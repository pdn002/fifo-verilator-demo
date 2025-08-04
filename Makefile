tb_files = fifo_tb.cpp
tb_wrap_files = fifo_tb.sv fifo_tb_wrap.cpp

.PHONY: all verilate compile simulate wave clean

default: simulate

wrap: simulate_wrap

##############################
# Run with the c++ Testbench #
##############################
verilate: fifo.sv fifo_tb.cpp
	verilator --cc --exe -f filelist $(tb_files)

compile: verilate
	make -C obj_dir -f Vfifo.mk Vfifo

simulate: compile
	./obj_dir/Vfifo

##############################################
# Run with a C++ wrapper around SV testbench #
##############################################
verilate_wrap: fifo.sv fifo_tb.cpp
	verilator --cc --exe -top fifo_tb -f filelist $(tb_wrap_files)

compile_wrap: verilate_wrap
	make -C obj_dir -f Vfifo_tb.mk Vfifo_tb

simulate_wrap: compile_wrap
	./obj_dir/Vfifo_tb



wave: fifo_tb.vcd
	gtkwave fifo_tb.vcd

clean:
	rm -rf obj_dir
	rm -rf fifo_tb.vcd