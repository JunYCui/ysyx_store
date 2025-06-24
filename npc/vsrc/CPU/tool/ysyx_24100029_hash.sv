module ysyx_24100029_hash(
    input [31:0] data,
    output [2:0] hash_data
);

  assign hash_data = {
    data[0] ^ data[3] ^ data[6] ^ data[9] ^ data[12] ^ data[15] ^ data[18] ^ data[21] ^ data[24] ^ data[27] ^ data[30],
    data[1] ^ data[4] ^ data[7] ^ data[10] ^ data[13] ^ data[16] ^ data[19] ^ data[22] ^ data[25] ^ data[28] ^ data[31],
    data[2] ^ data[5] ^ data[8] ^ data[11] ^ data[14] ^ data[17] ^ data[20] ^ data[23] ^ data[26] ^ data[29]
  };

endmodule //hash

