module bitrev (
    input                                  sck                        ,
    input                                  ss                         ,
    input                                  mosi                       ,
    output                                 miso                        
);
    reg                [   7: 0]        rx                          ;
    reg                [   4: 0]        count                       ;
    reg                                 en                          ;
  always @(posedge sck) begin
      if(count == 5'd16)begin
        rx <= 0;
        count <= 0;
      end
      else if(!ss && count <8)begin
        rx <={rx[7:1],mosi};
        count <= count + 1;
      end
      else if(!ss && count >=8)begin
        count <= count + 1;
      end
  end
    assign                              miso                        = (count>=8)? rx[count-8]:1;

endmodule
