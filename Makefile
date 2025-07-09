.PHONY: all verilate compile simulate wave clean

all: simulate

verilate: fifo.sv fifo_tb.cpp
	verilator --cc --exe -f filelist

compile: verilate
	make -C obj_dir -f Vfifo.mk Vfifo

simulate: compile
	./obj_dir/Vfifo

wave: fifo_tb.vcd
	gtkwave fifo_tb.vcd

clean:
	rm -r obj_dir