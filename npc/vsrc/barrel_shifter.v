module barrel_shifter
(
    input din[7:0],
    input shamt[2:0],
    input dir,
    input ari,

    output dout[7:0]
);
    reg [7:0]din_1,din_2;
    always@(*)
    begin
        if(shamt[0] == 1'b1)
       begin
        if(ari == 1'b1)
            if(dir == 1'b1)
                din_1 = {din[6:0],1'b0};
            else 
                din_1 = {1'b0,din[7:1]};
        else
            if(dir == 1'b1)
                din_1 = {din[6:0],1'b0};
            else 
                din_1 = {din[7],din[7:1]};
       end
        else 
            din_1 = din; 
    end

    always@(*)
    begin
        if(shamt[1] == 1'b1)
       begin
        if(ari == 1'b1)
            if(dir == 1'b1)
                din_2 = {din_1[5:0],2'b00};
            else 
                din_2 = {2'b00,din_1[7:2]};
        else
            if(dir == 1'b1)
                din_2 = {din_1[5:0],2'b00};
            else 
                din_2 = {din_1[7],din_2[7],din_1[7:2]};
       end
        else 
            din_1 = din_2; 
    end

        always@(*)
    begin
        if(shamt[1] == 1'b1)
       begin
        if(ari == 1'b1)
            if(dir == 1'b1)
                dout = {din_2[4:0],3'b000};
            else 
                dout = {3'b000,din_2[7:3]};
        else
            if(dir == 1'b1)
                dout = {din_2[4:0],3'b000};
            else 
                dout = {din_2[7],din_2[7],din_2[7],din_2[7:3]};
       end
        else 
            dout = din_2; 
    end



endmodule