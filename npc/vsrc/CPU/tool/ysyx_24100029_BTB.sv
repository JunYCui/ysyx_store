module ysyx_24100029_BTB #(
        Way = 2,
        INDEX_WIDTH = 3
    )
    (
        input clock,
        input reset,
        input [31:0] btb_pc,
        output [32-1:0] btb_npc,

        output [2-1:0]btb_br_type,
        output btb_is_hit,

        input [31:0]btb_commit_pc,
        input [1:0]btb_commit_pc_type,
        input [31:0]btb_commit_npc,
        input btb_commit
    );

    // 随即替换

    localparam ADDR_WIDTH = 32;
    localparam OFFSET_WIDTH = 2          ;
    localparam TAG_WIDTH = 32 - INDEX_WIDTH - OFFSET_WIDTH;
    localparam BR_TYPE_WIDTH = 2;
    localparam VALID_WIDTH = 1;

    localparam IDLE = 1'b0;
    localparam MISS = 1'b1;

    localparam CACHELINE_WIDTH = ADDR_WIDTH + TAG_WIDTH + VALID_WIDTH + BR_TYPE_WIDTH;

    wire [INDEX_WIDTH-1:0]pc_index;
    wire [TAG_WIDTH-1:0]pc_tag;
    wire [INDEX_WIDTH-1:0]commit_pc_index;
    wire [TAG_WIDTH-1:0]commit_pc_tag;
    wire way_choice;
    wire [TAG_WIDTH-1:0]cache_tag[Way-1:0];
    // |0|valid|1:25|Tag|26:27|br_type0|28:59|btb_npc|

    reg [CACHELINE_WIDTH-1:0] Cache[2**INDEX_WIDTH-1:0][Way-1:0];
    reg count;


    always @(posedge clock ) begin
        if(btb_commit) begin
            if(Cache[commit_pc_index][0][0] == 1'b0) begin
                Cache[commit_pc_index][0][TAG_WIDTH + VALID_WIDTH-1:0] <= {commit_pc_tag,1'b1};
                Cache[commit_pc_index][0][VALID_WIDTH+TAG_WIDTH+BR_TYPE_WIDTH-1:VALID_WIDTH + TAG_WIDTH] <= btb_commit_pc_type;
                Cache[commit_pc_index][0][VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH+32-1:VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH] <= btb_commit_npc;
            end
            else if(Cache[commit_pc_index][1][0] == 1'b0) begin
                Cache[commit_pc_index][1][TAG_WIDTH + VALID_WIDTH-1:0] <= {commit_pc_tag,1'b1};
                Cache[commit_pc_index][1][VALID_WIDTH+TAG_WIDTH+BR_TYPE_WIDTH-1:VALID_WIDTH + TAG_WIDTH] <= btb_commit_pc_type;
                Cache[commit_pc_index][1][VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH+32-1:VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH] <= btb_commit_npc;
            end
            else begin
                Cache[commit_pc_index][count][TAG_WIDTH + VALID_WIDTH-1:0] <= {commit_pc_tag,1'b1};
                Cache[commit_pc_index][count][VALID_WIDTH+TAG_WIDTH+BR_TYPE_WIDTH-1:VALID_WIDTH + TAG_WIDTH] <= btb_commit_pc_type;
                Cache[commit_pc_index][count][VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH+32-1:VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH] <= btb_commit_npc;               
            end
        end
    end

    always @(posedge clock) begin
        if(reset)
            count <= 1'b0;
        else 
            count <= count + 1;
    end

    assign commit_pc_index = btb_commit_pc[OFFSET_WIDTH+INDEX_WIDTH-1:OFFSET_WIDTH];
    assign commit_pc_tag = btb_commit_pc[31:OFFSET_WIDTH+INDEX_WIDTH];
    assign pc_index = btb_pc[OFFSET_WIDTH+INDEX_WIDTH-1:OFFSET_WIDTH];
    assign pc_tag = btb_pc[31:OFFSET_WIDTH+INDEX_WIDTH];

    assign cache_tag[0] = Cache[pc_index][0][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];
    assign cache_tag[1] = Cache[pc_index][1][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];

    assign btb_br_type = Cache[pc_index][way_choice][VALID_WIDTH+TAG_WIDTH+BR_TYPE_WIDTH-1:VALID_WIDTH+TAG_WIDTH] ;

    assign btb_is_hit = ((pc_tag == cache_tag[0])& Cache[pc_index][0][0]) ||
           ((pc_tag == cache_tag[1])& Cache[pc_index][1][0]);

    assign way_choice = pc_tag == cache_tag[1];

    assign btb_npc=Cache[pc_index][way_choice][VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH+32-1:VALID_WIDTH + BR_TYPE_WIDTH + TAG_WIDTH] ;



endmodule //BTB

