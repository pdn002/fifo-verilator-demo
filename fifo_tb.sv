module fifo_tb;
    reg clk, reset;
    reg wen, ren;
    reg [3:0] din;
    wire [3:0] dout;
    wire empty, full;

    integer i;

    logic done;


    fifo #() fifo_1 (
        .clk(clk), .reset(reset), 
        .wen(wen), .ren(ren), 
        .wdata(din), 
        .rdata(dout), 
        .empty(empty), .full(full)
    );

    initial begin
        wait(done);
        $display("\nTestbench done\n");
        #20 $finish;
    end

    initial begin
        clk = 0;
        reset = 0;
        wen = 0;
        ren = 0;
        din = 0;
        done = 0;

        $dumpfile("fifo_tb.vcd");
        $dumpvars(0, fifo_tb);

        $display("here 1\n");

        #5 clk = 0;
        $display("here 2\n");
        reset = 1;
        #5 clk = 1;

        for (i = 0; i < 5; i=i+1) begin
            #5 clk = 0;
            #5 clk = 1;
        end

        #5 clk = 0;
        reset = 0;
        #5 clk = 1;

        for (i = 0; i < 18; i=i+1) begin
            #5 clk = 0;
            wen = 1;
            din = i[3:0];
            $display("writing %d", i);
            if (full) begin
                $display("fifo is full");
            end
            #5 clk = 1;
        end

        #5 clk = 0;
        wen = 0;
        #5 clk = 1;

        for (i = 0; i < 18; i=i+1) begin
            #5 clk = 0;
            ren = 1;
            $display("read %d", dout);
            if (empty) begin
                $display("fifo is empty");
            end
            #5 clk = 1;
        end

        #5 clk = 0;
        ren = 0;
        #5 clk = 1;

        done = 1;

    end
endmodule
