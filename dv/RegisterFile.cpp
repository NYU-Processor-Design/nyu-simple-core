#include <catch2/catch_test_macros.hpp>
#include <random>
#include <VRegisterFile.h>

static VRegisterFile rf;

static auto tick = [](int ticks = 1) {
  for(int i {0}; i < ticks; ++i) {
    rf.clk = 0;
    rf.eval();
    rf.clk = 1;
    rf.eval();
  }
};

static auto init = [] {
  rf.nReset = 1;
  rf.eval();
  rf.nReset = 0;
  rf.eval();
  rf.nReset = 1;
};

TEST_CASE("Register File, Write 0") {
  init();

  rf.srcA = 0;
  rf.srcB = 0;
  rf.dst = 0;
  rf.inData = 1;
  rf.we = 0;

  tick();

  REQUIRE(rf.outDataA == 0);
  REQUIRE(rf.outDataB == 0);

  rf.we = 1;

  tick(2);

  REQUIRE(rf.outDataA == 0);
  REQUIRE(rf.outDataB == 0);
}

TEST_CASE("Register File, Write/Read with we=1") {
  init();

  rf.srcA = 0;
  rf.srcB = 0;
  rf.inData = 0;
  rf.we = 1;

  for(int i {1}; i < 32; ++i) {
    rf.dst = i;
    rf.inData = 0;
    tick();

    rf.srcA = i;
    rf.srcB = i;
    tick();

    REQUIRE(rf.outDataA == 0);
    REQUIRE(rf.outDataB == 0);

    rf.inData = i;
    tick(2);

    REQUIRE(rf.outDataA == i);
    REQUIRE(rf.outDataB == i);
  }
}


TEST_CASE("Register File, Write/Read with we=0") {
  init();

  rf.srcA = 0;
  rf.srcB = 0;
  rf.inData = 0;
  rf.we = 1;

  for(int i {1}; i < 32; ++i) {
    rf.dst = i;
    rf.inData = i;
    tick();
  }

  rf.we = 0;

  for(int i {0}; i < 32; ++i) {
    rf.srcA = i;
    rf.srcB = i;
    tick();

    REQUIRE(rf.outDataA == i);
    REQUIRE(rf.outDataB == i);
  }
}
