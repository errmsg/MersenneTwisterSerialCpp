// test code for mersenne twister
#include "../include/mt_serial.h"
#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"


TEST_CASE( "Random numbers are generated", "[seed]" ) {
  // Initialize with a seed
  unsigned long long initialSeed = 127;
  init_genrand64(initialSeed);
  // Test cases (results are casted to unsigned long long, ULL)
  REQUIRE( genrand64_int64() ==  5044285217761093508ULL);
  REQUIRE( genrand64_int64() ==  3905228834498165075ULL);
  REQUIRE( genrand64_int64() ==  11266652706158446358ULL);
  REQUIRE( genrand64_int64() ==  5291978865493110872ULL);
  REQUIRE( genrand64_int64() ==  17877536607980909229ULL);
}
