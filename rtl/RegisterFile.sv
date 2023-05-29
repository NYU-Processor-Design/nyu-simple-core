module RegisterFile #(WordSize = 32)
(
  input clk,
  input nReset,
  input we,

  input [4:0] srcA,
  input [4:0] srcB,
  input [4:0] dst,

  input [WordSize-1:0] inData,
  output logic [WordSize-1:0] outDataA,
  output logic [WordSize-1:0] outDataB
);


  logic [WordSize-1:0] registers[31];
  always_ff @(posedge clk, negedge nReset) begin
    if(!nReset)
      for(int i = 0; i < $size(registers); ++i)
        registers[i] <= 0;

    if(we && |dst)
      registers[dst - 1] <= inData;

    outDataA <= |srcA ? registers[srcA - 1] : 0;
    outDataB <= |srcB ? registers[srcB - 1] : 0;

  end

endmodule
