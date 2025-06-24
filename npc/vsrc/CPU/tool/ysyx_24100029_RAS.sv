module ysyx_24100029_RAS #(
        Depth = 8
    )
    (
        input clock,
        input reset,

        input [31:0]waddr,
        input ras_w_en,
        input ras_r_en,
        output [31:0]raddr
    );
    logic empty;
    logic [$clog2(Depth)-1:0]w_ptr;
    logic [$clog2(Depth):0] count;
    logic [31:0] LIFO [Depth-1:0];

    always @(posedge clock) begin
        if(ras_w_en)
            LIFO[w_ptr] <= waddr;
    end
    always @(posedge clock) begin
        if(reset)
            w_ptr <= 0;
        else if (ras_w_en)
            w_ptr <= w_ptr + 1;
        else if(ras_r_en & ~empty)
            w_ptr <= w_ptr - 1;
    end

    always @(posedge clock) begin
        if(reset)
            count <= 0;
        else if (ras_w_en & ~(count == Depth))
            count <= count + 1;
        else if(ras_r_en & empty)
            count <= count - 1;
    end

    assign raddr = LIFO [w_ptr-1];
    assign empty = count == 0;


endmodule //RAS

