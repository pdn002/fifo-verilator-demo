#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo.h"

using namespace std;

vluint64_t sim_time = 0; // vluint64_t is likely a typedef defined in verilator
Vfifo *fifo_1;
VerilatedVcdC *m_trace;

void eval_clk(int level){
    fifo_1->clk = level;
    fifo_1->eval();
    m_trace->dump(sim_time);
    sim_time++;
}

int main(int argc, char** argv){
    fifo_1 = new Vfifo();

    Verilated::traceEverOn(true);
    m_trace = new VerilatedVcdC();
    fifo_1->trace(m_trace, 5);
    m_trace->open("fifo_tb.vcd");

    fifo_1->reset = 0;
    fifo_1->wen = 0;
    fifo_1->ren = 0;
    fifo_1->wdata = 0;
    eval_clk(0);
    
    fifo_1->clk = 0;
    fifo_1->reset = 1;
    eval_clk(0);
    eval_clk(1);


    for (int i = 0; i < 5; i++) {
        eval_clk(0);
        eval_clk(1);
    }

    fifo_1->reset = 0;
    eval_clk(0);
    eval_clk(1);

    for (int i = 0; i < 18; i=i+1) {
        fifo_1->wen = 1;
        fifo_1->wdata = i;
        cout << "writing " << i;
        if (fifo_1->full) {
            cout << " but fifo is full" << endl;
        }
        else{
            cout << endl;
        }
        eval_clk(0);
        eval_clk(1);
    }

    fifo_1->wen = 0;
    eval_clk(0);
    eval_clk(1);
    
    for (int i = 0; i < 18; i=i+1) {
        fifo_1->ren = 1;
        cout << "read " << (int)(fifo_1->rdata);
        if (fifo_1->empty) {
            cout << " but fifo is empty" << endl;
        }
        else{
            cout << endl;
        }
        eval_clk(0);
        eval_clk(1);
    }

    fifo_1->ren = 0;
    eval_clk(0);
    eval_clk(1);


    for (int i = 0; i < 4; i++){
        eval_clk(0);
    }

    m_trace->close();
    delete fifo_1;
    exit(EXIT_SUCCESS);
}