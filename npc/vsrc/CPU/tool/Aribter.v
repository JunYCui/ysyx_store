/* Deal with the Data hazard */

module Aribter(
    input              [   4: 0] IDU_rs1                    ,
    input              [   4: 0] IDU_rs2                    ,

    input              [   4: 0] EXU_rd                     ,
    input              [   4: 0] WBU_rd                     ,
    input              [   4: 0] MEM_rd                     ,

    input                        IDU_valid                  ,
    input                        EXU_valid                  ,
    input                        MEM_valid                  ,
    input                        WBU_valid                  ,

    input                        MEM_mem_ren                ,
    input                        EXU_R_Wen                  ,
    input                        WBU_R_Wen                  ,
    input                        MEM_R_Wen                  ,

    output             [   2: 0] IDU_rs1_choice             ,
    output             [   2: 0] IDU_rs2_choice              
);

assign IDU_rs1_choice = (EXU_R_Wen && (EXU_rd == IDU_rs1 && EXU_rd != 0 && IDU_valid && EXU_valid))? 
                        3'b001:(WBU_R_Wen   && (WBU_rd == IDU_rs1) && WBU_valid && IDU_valid)?
                        3'b010:(MEM_mem_ren && (MEM_rd == IDU_rs1 && MEM_valid && IDU_valid))?
                        3'b011:(MEM_R_Wen &&~MEM_mem_ren && (MEM_rd == IDU_rs1) && MEM_valid && IDU_valid )?
                        3'b100:3'b000                         ;

assign IDU_rs2_choice = (EXU_R_Wen && (EXU_rd == IDU_rs2 && EXU_rd != 0)&& IDU_valid && EXU_valid)? 
                        3'b001:(WBU_R_Wen   && (WBU_rd == IDU_rs2) && WBU_valid && IDU_valid)?
                        3'b010:(MEM_mem_ren && (MEM_rd == IDU_rs2)&& MEM_valid && IDU_valid)?
                        3'b011:(MEM_R_Wen &&~MEM_mem_ren && (MEM_rd == IDU_rs2)&& MEM_valid && IDU_valid)?
                        3'b100:3'b000                         ;

endmodule                                                           //Aribter



