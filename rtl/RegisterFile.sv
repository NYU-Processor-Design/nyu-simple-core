module RegisterFile #(
    int WordSize = 32
) (
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

  logic [WordSize-1:0] registers[1:31];

  always_ff @(posedge clk, negedge nReset) begin
    // verilog_format: off
    if (!nReset)
      for (int i = 0; i < $size(registers); ++i)
        registers[i] <= 0;

    if (we && |dst)
      registers[dst] <= inData;
    // verilog_format: on

    outDataA <= |srcA ? registers[srcA] : 0;
    outDataB <= |srcB ? registers[srcB] : 0;

  end

endmodule
