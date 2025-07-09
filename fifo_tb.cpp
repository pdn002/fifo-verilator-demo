#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vfifo.h"
#include "Vfifo___024root.h"

using namespace std;

#define MAX_SIM_TIME 20
vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env){
    Vfifo *fifo_1 = new Vfifo();

    fifo_1->clk = 0;
    fifo_1->reset = 0;
    fifo_1->wen = 0;
    fifo_1->ren = 0;
    fifo_1->wdata = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    fifo_1->trace(m_trace, 5);
    m_trace->open("fifo_tb.vcd");
    
    sim_time++;
    fifo_1->clk = 0;
    fifo_1->reset = 1;
    fifo_1->eval();
    m_trace->dump(sim_time);
    sim_time++;
    fifo_1->clk = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);


    for (int i = 0; i < 5; i++) {
        sim_time++;
        fifo_1->clk = 0;
        fifo_1->eval();
        m_trace->dump(sim_time);
    }

    sim_time++;
    fifo_1->clk = 0;
    fifo_1->reset = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);
    sim_time++;
    fifo_1->clk = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);

    for (int i = 0; i < 18; i=i+1) {
        sim_time++;
        fifo_1->clk = 0;
        fifo_1->wen = 1;
        fifo_1->wdata = i;
        cout << "writing " << i << endl;
        if (fifo_1->full) {
            cout << "fifo is full" << endl;
        }
        fifo_1->eval();
        m_trace->dump(sim_time);
        sim_time++;
        fifo_1->clk = 1;
        fifo_1->eval();
        m_trace->dump(sim_time);
    }

    sim_time++;
    fifo_1->clk = 0;
    fifo_1->wen = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);
    sim_time++;
    fifo_1->clk = 1;
    fifo_1->eval();
    m_trace->dump(sim_time);
    
    for (int i = 0; i < 18; i=i+1) {
        sim_time++;
        fifo_1->clk = 0;
        fifo_1->ren = 1;
        cout << "writing " << (int)(fifo_1->rdata) << endl;
        if (fifo_1->empty) {
            cout << "fifo is full" << endl;
        }
        fifo_1->eval();
        m_trace->dump(sim_time);
        sim_time++;
        fifo_1->clk = 1;
        fifo_1->eval();
        m_trace->dump(sim_time);
    }

    sim_time++;
    fifo_1->clk = 0;
    fifo_1->ren = 0;
    fifo_1->eval();
    m_trace->dump(sim_time);
    sim_time++;
    fifo_1->clk = 1;
    fifo_1->eval();
    m_trace->dump(sim_time);

    sim_time = sim_time + 4;
    fifo_1->eval();
    m_trace->dump(sim_time);


    m_trace->close();
    delete fifo_1;
    exit(EXIT_SUCCESS);
}