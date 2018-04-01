
#define CATCH_CONFIG_MAIN

#include <vector>
#include <memory>
#include "catch.hpp"
#include "Shape.h"


TEST_CASE( "Circle height and width", "[multi-file:1]" ) {
  REQUIRE (Circle(1).height() == 2);
  REQUIRE (Circle(1).width() == 2);
  REQUIRE (Circle(4).width() == 8);
  REQUIRE (Circle(4).height() == 8);
  REQUIRE (Circle(100).width() == 200);
  REQUIRE (Circle(100).height() == 200);
  REQUIRE (Circle(-1).width() == -2.0);
  REQUIRE (Circle(-1).height() == -2.0);
}

// TEST_CASE( "Square Tests", "[multi-file:1]" ) {
//   REQUIRE (Circle(1).height() == 2);
//   REQUIRE (Circle(1).width() == 2);
//   REQUIRE (Circle(4).width() == 8);
//   REQUIRE (Circle(4).height() == 8);
//   REQUIRE (Circle(100).width() == 200);
//   REQUIRE (Circle(100).height() == 200);
//   REQUIRE (Circle(-1).width() == -2.0);
//   REQUIRE (Circle(-1).height() == -2.0);
// }

TEST_CASE( "Rectangle Tests", "[multi-file:1]" ) {
  REQUIRE (Rectangle(1,1).height() == 1);
  REQUIRE (Rectangle(1,1).width() == 1);
  REQUIRE (Rectangle(5,5).width() == 5);
  REQUIRE (Rectangle(5,5).height() == 5);
  REQUIRE (Rectangle(-1,-1).width() == -1);
  REQUIRE (Rectangle(-1,-1).height() == -1);
}

TEST_CASE ( "toPostscript tests") {
  //std::vector<std::string> testShapes;
  //testShapes.emplace_back(Circle(1).toPostScript());
  REQUIRE (Circle(1).toPostScript() == "gsave \n currentpoint 1 0 360 arc stroke \ngrestore \n");
}

TEST_CASE ( "Vertical shape of 2 shapes height and width") {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.emplace_back(std::make_unique<Circle>(1));
  shapes.emplace_back(std::make_unique<Circle>(5));
  std::unique_ptr<Shape> vertical = std::make_unique<Vertical>(std::move(shapes));
  
  REQUIRE (vertical->height() == 12.0);
}

TEST_CASE ("Rotate Constructor") {
  std::unique_ptr<Rotate> rotatedCircle = std::make_unique<Rotate>(std::make_unique<Circle>(1), 90);
  REQUIRE (rotatedCircle->angle() == 90);
  std::unique_ptr<Rotate> rotatedCircle2 = std::make_unique<Rotate>(std::make_unique<Circle>(1), 270); 
  REQUIRE (rotatedCircle2->angle() == 270);
  std::unique_ptr<Rotate> rotatedCircle3 = std::make_unique<Rotate>(std::make_unique<Circle>(1), -100); 
  REQUIRE (rotatedCircle3->angle() == 0);
  std::unique_ptr<Rotate> rotatedCircle4 = std::make_unique<Rotate>(std::make_unique<Circle>(1), 100000); 
  REQUIRE (rotatedCircle4->angle() == 0);
}