module fifo #(parameter depth_bw=4, parameter data_bw=4) (
    input clk, reset, 
    input wen, ren, 
    input [data_bw-1:0] wdata /* verilator public */, 
    output [data_bw-1:0] rdata, 
    output empty, 
    output full);

    reg [data_bw-1:0] fifo_mem [1<<depth_bw];

    reg [depth_bw:0] rd_ptr /* verilator public */;
    reg [depth_bw:0] wr_ptr /* verilator public */;

    assign rdata = fifo_mem[rd_ptr[depth_bw-1:0]];

    assign empty = (rd_ptr == wr_ptr);
    assign full = (rd_ptr[depth_bw-1:0] == wr_ptr[depth_bw-1:0] && rd_ptr[depth_bw] != wr_ptr[depth_bw]);

    always @(posedge clk) begin
        if (reset) begin
            rd_ptr <= 0;
            wr_ptr <= 0;
        end
        else begin
            if (ren && !empty) begin
                rd_ptr <= rd_ptr + 1;
            end
            if (wen && !full) begin
                fifo_mem[wr_ptr[depth_bw-1:0]] <= wdata;
                wr_ptr <= wr_ptr + 1;
            end
        end
    end

endmodule
