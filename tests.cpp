
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Shape.h"

TEST_CASE( "Circle of positive radius height and width", "[multi-file:1]" ) {
  REQUIRE (Circle(1).height() == 2);
  REQUIRE (Circle(1).width() == 2);
  REQUIRE (Circle(4).width() == 8);
  REQUIRE (Circle(4).height() == 8);
  REQUIRE (Circle(100).width() == 200);
  REQUIRE (Circle(100).height() == 200);
}

TEST_CASE ( "Circle of negative radius") {
  REQUIRE (Circle(-1).width() == -2.0);
  REQUIRE (Circle(-1).height() == -2.0);
}