#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo_tb.h"

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

    delete fifo_tb_1;
    delete contextp;

    return 0;
}