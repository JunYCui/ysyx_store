module ps2_top_apb(
    input                                  logic                               clock,
    input                                  logic                               reset,
    input                                  logic           [  31: 0]           in_paddr,
    input                                  logic                               in_psel,
    input                                  logic                               in_penable,
    input                                  logic           [   2: 0]           in_pprot,
    input                                  logic                               in_pwrite,
    input                                  logic           [  31: 0]           in_pwdata,
    input                                  logic           [   3: 0]           in_pstrb,
    output                                 logic                               in_pready,
    output                                 logic           [  31: 0]           in_prdata,
    output                                 logic                               in_pslverr,

    input                                  ps2_clk                    ,
    input                                  ps2_data                    
    );
    logic              [  10: 0]        buffer                      ;
    logic              [   2: 0]        ps2_clk_syn                 ;
    logic              [   3: 0]        count                       ;
    logic                               sampling                    ;

    logic                               fifo_ren                    ;
    logic                               fifo_wen                    ;
    logic                               fifo_full                   ;
    logic              [   7: 0]        data_o                      ;
    logic                               fifo_empty                  ;

    // sample falling and avoid
    assign                              sampling                    = ps2_clk_syn[2] & ~ps2_clk_syn[1];
    assign                              in_pready                   = in_psel & in_penable;
    assign                              fifo_ren                    = in_pready | fifo_full;
    assign                              in_pslverr                  = 0;

    always @(posedge clock) begin
        if(in_pready&~in_pwrite&in_paddr[3:0] == 4'd0) begin
            in_prdata[7:0] <= (fifo_empty)? 0:data_o;
        end
    end

    always @(posedge clock) begin
        ps2_clk_syn <= {ps2_clk_syn[1:0],ps2_clk};
    end
    always @(posedge clock or posedge reset) begin
        if(reset)
            count <= 4'd0;
        else if (sampling && count == 4'd10)
            count <= 4'd0;
        else if(sampling)
            count <= count + 1;
    end

    always @(posedge clock or posedge reset) begin
        if(reset)
            buffer <= 0;
        else if(sampling)
            buffer[count] <= ps2_data;
    end


    // buffer[0]: start bit
    // buffer[8:1] data  ^buffer[1:8] odd
    // buffer[9] stop bit
    assign                              fifo_wen                    = (sampling & count == 4'd10) & (~buffer[0]) & (^buffer[9:1]) & ps2_data;

    fifo fifo_inst(
    .clk                                (clock                     ),
    .clr                                (reset                     ),
    .w_en                               (fifo_wen                  ),
    .r_en                               (fifo_ren                  ),
    .dat_i                              (buffer[8:1]               ),
    .dat_o                              (data_o                    ),
    .full                               (fifo_full                 ),
    .empty                              (fifo_empty                ) 

         );


endmodule

module fifo(
    input                                  clk                        ,
    input                                  clr                        ,
    input                                  w_en                       ,
    input                                  r_en                       ,
    input              [   7: 0]           dat_i                      ,
    output             [   7: 0]           dat_o                      ,
    output                                 full                       ,
    output                                 empty                       
    );

    reg                [   3: 0]        r_ptr                       ;// read index
    reg                [   3: 0]        w_ptr                       ;// write index
    reg                [   7: 0]        fifo[7:0]                   ;// depth = 8

    always @(posedge clk or posedge clr) begin
        if(clr) begin
            r_ptr <= 0;
            w_ptr <= 0;
        end
        else begin
            if(w_en & ~full) begin
                fifo[w_ptr[2:0]] <= dat_i;
                w_ptr <= w_ptr + 1;
            end
            if(r_en & ~empty) begin
                r_ptr <= r_ptr + 1;
            end
        end
    end

    assign                              full                        = (w_ptr[3]!=r_ptr[3]) && (w_ptr[2:0] == r_ptr[2:0]);// it means w_ptr - r_ptr = 8
    assign                              empty                       = (w_ptr == r_ptr);
    assign                              dat_o                       = fifo[r_ptr[2:0]];


endmodule
