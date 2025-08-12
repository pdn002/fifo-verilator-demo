#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo_tb.h"
// needs the following includes for accessing deeper ports and signals 
// maked with /* verilator public */
#include "Vfifo_tb_fifo_tb.h"
#include "Vfifo_tb_fifo.h"

using namespace std;

vluint64_t sim_time = 0; // vluint64_t is likely a typedef defined in verilator
Vfifo_tb *fifo_tb_1;
VerilatedContext *contextp;

int main(int argc, char** argv){

    contextp = new VerilatedContext();

    contextp->commandArgs(argc, argv);

    contextp->traceEverOn(true);

    fifo_tb_1 = new Vfifo_tb(contextp);

    while (!contextp->gotFinish()){
        fifo_tb_1->eval();
        contextp->timeInc(1);
    }

    // example of accessing deeper internal signals in hierarchy
    fifo_tb_1->fifo_tb->fifo_1->rd_ptr = 5;
    cout << "rd_ptr: " << (int)fifo_tb_1->fifo_tb->fifo_1->rd_ptr << endl;
    // example of accessing deeper module ports in hierarchy
    fifo_tb_1->fifo_tb->fifo_1->wdata = 6;
    cout << "wdata: " << (int)fifo_tb_1->fifo_tb->fifo_1->wdata << endl;

    delete fifo_tb_1;
    delete contextp;

    return 0;
}