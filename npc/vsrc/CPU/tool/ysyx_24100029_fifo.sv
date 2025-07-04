module ysyx_24100029_fifo #(
    parameter DATA_WIDTH = 8,  // FIFO数据位宽
    parameter FIFO_DEPTH = 16  // FIFO深度（条目数，必须是2的幂）
)(
    input  logic                  clk,      // 时钟
    input  logic                  rst,      // 异步复位（高电平有效）
    input  logic                  clr,
    input  logic                  wr_en,    // 写使能
    input  logic [DATA_WIDTH-1:0] data_in,  // 写入数据
    input  logic                  rd_en,    // 读使能
    output logic [DATA_WIDTH-1:0] data_out, // 读出数据
    output logic                  full,     // FIFO满标志
    output logic                  empty     // FIFO空标志
);

    // FIFO存储器（基于寄存器）
    logic [DATA_WIDTH-1:0] mem [FIFO_DEPTH-1:0];

    // 读写指针（二进制编码）
    logic [$clog2(FIFO_DEPTH)-1:0] wr_ptr, rd_ptr;

    // 指针比较标志
    logic [$clog2(FIFO_DEPTH):0] cnt;              // 当前FIFO数据计数

    // ------------------------
    // FIFO控制逻辑
    // ------------------------
    always_ff @(posedge clk) begin
        if (rst|clr) begin
            wr_ptr       <= 0;
            rd_ptr       <= 0;
            cnt          <= 0;
        end else begin
            // 写操作
            if (wr_en && !full) begin
                mem[wr_ptr] <= data_in;
                wr_ptr      <= wr_ptr + 1'b1;
            end

            // 读操作
            if (rd_en && !empty) begin
                rd_ptr   <= rd_ptr + 1'b1;
            end

            // 更新数据计数
            case ({wr_en, rd_en})
                2'b01 : cnt <= cnt - 1'b1;  // 只读
                2'b10 : cnt <= cnt + 1'b1;  // 只写
                default: cnt <= cnt;        // 不变
            endcase
        end
    end

    // ------------------------
    // 状态标志逻辑
    // ------------------------
    assign full          = (cnt == FIFO_DEPTH);                // 已满
    assign empty         = (cnt == 0);                         // 已空
    assign data_out      = mem[rd_ptr];

endmodule
