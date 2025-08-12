# FIFO Verilator Demo

## About
The main goal of this project is to learn the basics of Verilator by applying using it to simulate a simple fifo. <br>

- fifo.sv is the top module and the only module in the design
- fifo_tb.cpp is a C++ testbench for the fifo design
- fifo_tb.sv is a SystemVerilog testbench for the fifo design
- fifo_tb_wrap.cpp is a C++ wrapper used for running the SystemVerilog testbench above
<br>

By default the fifo_tb.cpp testbench is used for testing instead of the fifo_tb.sv testbench. <br>
There is also a second option to simulate the fifo using the the System Verilog testbench with a C++ wrapper. The second option also demonstrates how parallel initial blocks can continue to be used in System Verilog even when starting with a C++ testbench.
<br> <br>
Option 1: Simulate with fifo_tb.cpp testbench
```
make
```
Option 2: Simulate with fifo_tb.sv tesbench that uses fifo_tb_wrap.cpp as a wrapper.
```
make wrap
```

The waveform can be viewed using GTKWave with the following command. <br>
```
make wave
```

## Verilator Installation
Verilator was installed with the [OSS CAD Suite](https://github.com/YosysHQ/oss-cad-suite-build/?tab=readme-ov-file).
In addition to Verilator, OSS CAD Suite also includes other open source software used in digital logic such as Yosys-ABC, iverilog, and GTKWave. <br>
To install [OSS CAD Suite](https://github.com/YosysHQ/oss-cad-suite-build/?tab=readme-ov-file), go to the repo and locate the releases tab. Download the file that corresponds operating system architecture that matches your machine. The following commands can be used to download and extract the tar file. <br>
```
wget [download URL]
tar -xzf [tar file name] -C [directory to extract to]
```
[This video](https://youtu.be/ALuaCai1W_0?t=69) by BitByte is a useful guide for the installation.

## Notes and Things Learned About Verilator
- For OSS CAD Suite, the C++ verilator libraries are located at 
```
oss-cad-suite/share/verilator/include
```
- Verilator does not yet support 4-state values such as X and Z
    - By default X and Z are instead initialed to 0
    - There is support to set X and Z to random values instead and it can be done by modifying commands on the command line and adding commands to the C++ testbench
    - More details on how to do so [here](https://itsembedded.com/dhd/verilator_2/)
- List of usefule arguments to the "verilator" 
    - -Wall : enables stricter warning
    - -Wno-fatal : prevents exting on warnings
    - -j <jobs> : enables multi-threading
    - --assert : enables SystemVerilog assertions
    - --trace-fst : dump as FST which is compressed version of VCD
    - --trace-structs : dump structs as human-readable format
    - --x-assign unique : all explicit Xs are replaced by a random constant value determined at runtime
    - --x-initial unique : all variables are randomly initialized (if +verilator+rand+reset+2 is passed to executable)
    - More detailed documentation on arguments [here](https://verilator.org/guide/latest/exe_verilator.html)
- The C/C++ extension on github give a linting warning when including the verilator libraries inside the C++ testbench
    - To fix this include the path of the verilator libraries to a JSON file (the exact steps are found is [this guide](https://code.visualstudio.com/docs/cpp/configure-intellisense))
- Module parameters cannot be modified by the C++ testbench at runtime.
    - Module parameters can only be added to C++ testbench for reading using the /* verilator public */ tag which will create a new header file with the parameter as a static variable
    ```
    // inside fifo.sv
    module fifo #(parameter depth_bw/*verilator public*/=4, parameter data_bw=4)

    // inside fifo_tb.cpp
    #include "Vfifo_fifo.h"
    ...
    int depth_bw = Vfifo_fifo::depth_bw;
    ```
    - Only way module parameter can be modified is before the SystemVerilog code has been translated to C++ using the -G option
- Signals and ports of deeper submodules can be accessed and modified from a C++ testbench
   - One was is adding the /* verilator public */ tag to the desired signals in the verilog files. There are a few examples in the C++ wrapper testbench.
   - Another way is to use the --public or --public-flat-rw verilator arguments which will mark all signals and/or ports as public. Look up online or read documentation for more specifics.
- The key to getting the C++ wrapper option to work was using the timeInc(1) method from the VerilatedContext() class in order to be able to advance simulation time from the C++ wrapper. This allows simulation to advance past delay statements in the SV initial blocks

## Useful Guides
- [VERILATOR Introduction Video](https://www.youtube.com/watch?v=ALuaCai1W_0)
- [itsembedded.com](https://itsembedded.com/dhd_list/)