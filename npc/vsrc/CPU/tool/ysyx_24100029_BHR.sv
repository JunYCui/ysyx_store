module ysyx_24100029_BHR #(
        parameter BHR_WIDTH = 3,
        parameter BHR_INDEX_WIDTH = 3
    ) (
        input clock,
        input reset,
        input is_taken,
        input [BHR_INDEX_WIDTH-1:0] bhr_index_w,
        input bhr_w_en,

        input [BHR_INDEX_WIDTH-1:0] bhr_index_r0,
        input [BHR_INDEX_WIDTH-1:0] bhr_index_r1,
        output [BHR_WIDTH-1:0] bhr_value0,
        output [BHR_WIDTH-1:0] bhr_value1       
    );
    logic [BHR_WIDTH-1:0] LSR_REG[2**BHR_INDEX_WIDTH-1:0];
    integer i;
    always @(posedge clock) begin
        if (reset) begin
            for (i = 0; i < 2 ** BHR_INDEX_WIDTH; i = i + 1)
                LSR_REG[i] <= 0;
        end
        else if (bhr_w_en)
            LSR_REG[bhr_index_w] <= {LSR_REG[bhr_index_w][BHR_WIDTH-2:0], is_taken};
    end

    assign bhr_value0 = LSR_REG[bhr_index_r0];
    assign bhr_value1 = LSR_REG[bhr_index_r1];

endmodule  //bhr

