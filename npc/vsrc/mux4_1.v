module mux4_1
(
    input din0,
    input din1,
    input din2,
    input din3,
    input s0,
    input s1,

    output out
);
    always(*)
    begin
        case({s1,s0})

        2'b00:out <= din0; 
        2'b01:out <= din1;
        2'b10:out <= din2;
        2'b11:out <= din3;
        
        endcase 
    end




endmodule