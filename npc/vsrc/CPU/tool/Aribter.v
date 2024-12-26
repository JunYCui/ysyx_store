/* Deal with the Data hazard */

module Aribter(
    input              [   4: 0] IDU_rs1                        ,
    input              [   4: 0] IDU_rs2                        ,

    input              [   4: 0] EXU_rd                     ,
    input              [   4: 0] WBU_rd                     ,
    input                        EXU_R_Wen                  ,
    input                        WBU_R_Wen                  ,

    output             [   1: 0] IDU_rs1_choice             ,
    output             [   1: 0] IDU_rs2_choice              
);

assign IDU_rs1_choice = (EXU_R_Wen && (EXU_rd == IDU_rs1 && EXU_rd != 0))? 
                        2'b01:(WBU_R_Wen && (WBU_rd == IDU_rs1))?
                        2'b10:2'b00                         ;

assign IDU_rs2_choice = (EXU_R_Wen && (EXU_rd == IDU_rs2 && EXU_rd != 0))? 
                        2'b01:(WBU_R_Wen && (WBU_rd == IDU_rs2))?
                        2'b10:2'b00                         ;

endmodule                                                           //Aribter



