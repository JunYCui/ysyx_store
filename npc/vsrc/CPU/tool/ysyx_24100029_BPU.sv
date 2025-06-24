module ysyx_24100029_BPU #(
    parameter                           BHR_WIDTH                  = 3
    )
(
    input                               clock                      ,
    input                               reset                      ,
    // commit
    input                               br_valid                   ,
    input                               br_is_taken                ,
    input              [  31: 0]        br_pc                      ,
    input              [   1: 0]        br_pc_type                 ,
    input              [  31: 0]        br_npc                     ,

    input                               pc_update                  ,
    input              [  31: 0]        pc                         ,
    output             [  31: 0]        npc                        ,
    output                              pred_res                   
);

    localparam                          BHR_INDEX_WIDTH            = 3     ;
    localparam                          PC_INDEX_WIDTH             = 2     ;
    localparam                          BR_TYPE_CALL               = 2'b01 ;
    localparam                          BR_TYPE_RET                = 2'b10 ;
    localparam                          PHT_INDEX_WIDTH            = PC_INDEX_WIDTH + BHR_WIDTH;


    // declaration of module BHR
    logic [BHR_WIDTH-1:0] bhr_value0;
    logic [BHR_WIDTH-1:0] bhr_value1;
    logic bhr_w_en;
    logic [BHR_INDEX_WIDTH-1:0] bhr_index_w;
    logic [BHR_INDEX_WIDTH-1:0] bhr_index_r0;
    logic [BHR_INDEX_WIDTH-1:0] bhr_index_r1;

    // declaration of module PHT
    logic  pht_state;

    logic [PHT_INDEX_WIDTH-1:0] pht_index_w;
    logic [PHT_INDEX_WIDTH-1:0] pht_index_r;
    logic pht_w_en;

    // declaration of module RAS
    logic [31:0]ras_waddr;
    logic [31:0]ras_raddr;
    logic ras_w_en;
    logic ras_r_en;

    // declaration of module BTB
    logic [31:0] btb_pc;
    logic  [31:0] btb_npc;
    logic  [1:0]btb_br_type;
    logic  btb_is_hit;
    logic [31:0]btb_commit_pc;
    logic [1:0]btb_commit_pc_type;
    logic [31:0]btb_commit_npc;
    logic btb_commit;


    // is_taken
    logic is_taken ;
    logic [31:0]dnpc;
    logic [31:0] incr;

    // aligned addr
    logic [31:0]pc_align;
    logic [31:0]br_pc_align;

    logic [31:0]snpc;


    // Ras Control
    assign                              ras_waddr                   = snpc;
    assign                              ras_w_en                    = (btb_br_type == BR_TYPE_CALL) & pc_update & is_taken & btb_is_hit;
    assign                              ras_r_en                    = (btb_br_type == BR_TYPE_RET) & pc_update & is_taken & btb_is_hit;


    // Pht Control
    assign                              pht_index_w                 = {bhr_value1,br_pc[2+:PC_INDEX_WIDTH]};
    assign                              pht_index_r                 = {bhr_value0,pc[2+:PC_INDEX_WIDTH]};
    assign                              pht_w_en                    = br_valid;

    // Bhr Control
    assign                              bhr_w_en                    = br_valid ;

    // BTB Control 
    assign                              btb_pc                      = pc;
    assign                              btb_commit_pc               = br_pc;
    assign                              btb_commit_pc_type          = br_pc_type;
    assign                              btb_commit_npc              = br_npc;
    assign                              btb_commit                  = br_valid & br_is_taken;

    // dnpc generates
    assign                              dnpc                        = (btb_br_type== BR_TYPE_RET)?   ras_raddr : btb_npc;

    // 判断是否跳转
    assign                              is_taken                    = pht_state&btb_is_hit;


    // snpc generates
    assign                              incr                        = 4;
    assign                              snpc                        = pc + incr;

    // npc generators
    assign                              npc                         = is_taken? dnpc : snpc;

    // every instr jump results
    assign                              pred_res                    = is_taken;
    // 16 bytes align
    assign                              pc_align                    = {pc[31:2],2'd0};
    assign                              br_pc_align                 = {br_pc[31:2],2'd0};
    assign                              bhr_index_r1                = bhr_index_w;



    ysyx_24100029_BTB #(
    .Way                                (2                         ),
    .INDEX_WIDTH                        (3                         ) 
        ) u_BTB(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .btb_pc                             (btb_pc                    ),
    .btb_npc                            (btb_npc                   ),
    .btb_br_type                        (btb_br_type               ),
    .btb_is_hit                         (btb_is_hit                ),
    .btb_commit_pc                      (btb_commit_pc             ),
    .btb_commit_pc_type                 (btb_commit_pc_type        ),
    .btb_commit_npc                     (btb_commit_npc            ),
    .btb_commit                         (btb_commit                ) 
        );


    ysyx_24100029_RAS u_RAS(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .waddr                              (ras_waddr                 ),
    .ras_w_en                           (ras_w_en                  ),
    .ras_r_en                           (ras_r_en                  ),
    .raddr                              (ras_raddr                 ) 
        );




    ysyx_24100029_BHR #(
    .BHR_WIDTH                          (BHR_WIDTH                 ),
    .BHR_INDEX_WIDTH                    (BHR_INDEX_WIDTH  )        ) 
        u_BHR(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .is_taken                           (br_is_taken               ),
    .bhr_index_w                        (bhr_index_w               ),
    .bhr_w_en                           (bhr_w_en                  ),
    .bhr_index_r0                       (bhr_index_r0              ),
    .bhr_index_r1                       (bhr_index_r1              ),

    .bhr_value0                         (bhr_value0                ),
    .bhr_value1                         (bhr_value1                ) 
        );



    ysyx_24100029_PHT #(
    .PHT_INDEX_WIDTH                    (PHT_INDEX_WIDTH           ) 
        )
        u_PHT(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .pht_index_w                        (pht_index_w               ),
    .is_taken                           (br_is_taken               ),
    .pht_w_en                           (pht_w_en                  ),
    .pht_index_r                        (pht_index_r               ),

    .pht_state                          (pht_state                 ) 
        );



    ysyx_24100029_hash u_hash (
    .data                               (br_pc_align               ),
    .hash_data                          (bhr_index_w               ) 
         );

    ysyx_24100029_hash u_hash_1 (
    .data                               (pc_align                  ),
    .hash_data                          (bhr_index_r0              ) 
         );














endmodule

