#include "Car/Car/Car.h"
#include <catch2/catch.hpp>

//TurnOffEngine()

TEST_CASE("TurnOffEngine() on gear == 1 and speed == 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.TurnOffEngine() == false);
}

TEST_CASE("TurnOffEngine() on gear == -1 and speed == 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.TurnOffEngine() == false);
}

TEST_CASE("TurnOffEngine() on gear == 0 and speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.TurnOffEngine() == false);
}

TEST_CASE("TurnOffEngine() on gear != 0 and speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.TurnOffEngine() == false);
}

//SetGear()

TEST_CASE("SetGear() switch to 0 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to -1 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to 1 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 2 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 3 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 4 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 5 gear on engine off")
{
	Car car;
	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 0 ; speed = 0")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-1) == true);
}

TEST_CASE("SetGear() switch to -1 gear from gear = -1")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-1) == true);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 0 ; speed != 0 ; direction = Backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 0 ; speed != 0 ; direction = Forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 0 ; speed = 0 ;")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-1) == true);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 1 ; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.SetGear(-1) == true);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 1 ; speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 3")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 4")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(45);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to -1 gear from gear = 5")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(5);

	CHECK(car.SetGear(-1) == false);
}

TEST_CASE("SetGear() switch to 0 gear from gear = -1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 0")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 3")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 4")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(45);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 0 gear from gear = 5")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(5);

	CHECK(car.SetGear(0) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = -1; speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(1);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = -1; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetGear(1);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 0; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 0; speed != 0; direction = forward; speed in range 1 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	car.SetGear(1);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 0; speed != 0; direction = forward; speed not in range 1 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(0);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 0; speed != 0; direction = backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(1);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 2; speed in range gear 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(25);
	car.SetGear(2);
	car.SetSpeed(27);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 2; speed not in range gear 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(25);
	car.SetGear(2);
	car.SetSpeed(40);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 3; speed in range gear 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(1) == true);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 3; speed not in range gear 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 4")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);
	car.SetSpeed(70);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 1 gear from gear = 5")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);
	car.SetSpeed(70);
	car.SetGear(5);
	car.SetSpeed(150);

	CHECK(car.SetGear(1) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = -1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 0; speed != 0; direction = backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 0; speed != 0 in range; direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(0);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 0; speed != 0 not in range (upper); direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(0);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 0; speed != 0 not in range (lower); direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 1; speed not in range 2 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 1; speed in range 2 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 3; speed in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 3; speed not in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 4; speed in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 4; speed not in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 5; speed in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(5);

	CHECK(car.SetGear(2) == true);
}

TEST_CASE("SetGear() switch to 2 gear from gear = 5; speed not in range gear 2")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(5);
	car.SetSpeed(150);

	CHECK(car.SetGear(2) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = -1; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = -1; speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 0; speed != 0; direction = backward;")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 0; speed in range ; direction = forward;")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(0);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 0; speed not in range(upper); direction = forward;")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(0);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 0; speed not in range(lower); direction = forward;")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 1; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 1; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 2; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(25);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 2; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(40);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 3")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 4; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 4; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(50);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 5; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);
	car.SetSpeed(150);

	CHECK(car.SetGear(3) == false);
}

TEST_CASE("SetGear() switch to 3 gear from gear = 5; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);
	car.SetSpeed(60);

	CHECK(car.SetGear(3) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = -1; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = -1; speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 0; direction = backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 0; speed not in range (upper); direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(5);
	car.SetSpeed(150);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 0; speed not in range (lower); direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(0);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 0; speed in range; direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);

	CHECK(car.SetGear(4) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 2; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 2; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);

	CHECK(car.SetGear(4) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 3; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 3; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);

	CHECK(car.SetGear(4) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 4;")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);
	car.SetGear(4);

	CHECK(car.SetGear(4) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 5; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(5);

	CHECK(car.SetGear(4) == true);
}

TEST_CASE("SetGear() switch to 4 gear from gear = 5; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(5);
	car.SetSpeed(150);

	CHECK(car.SetGear(4) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = -1; speed = 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = -1; speed != 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 0; direction = backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 0; speed in range ; direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);
	car.SetGear(0);

	CHECK(car.SetGear(5) == true);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 0; speed not in range (lower); direction = forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 1")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 2; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);

	CHECK(car.SetGear(5) == true);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 2; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 3; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 3; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);

	CHECK(car.SetGear(5) == true);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 4; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);

	CHECK(car.SetGear(5) == false);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 4; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(50);

	CHECK(car.SetGear(5) == true);
}

TEST_CASE("SetGear() switch to 5 gear from gear = 5;")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(50);
	car.SetGear(5);

	CHECK(car.SetGear(5) == true);
}

TEST_CASE("SetGear() invalid gear (lower)")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(-2) == false);
}

TEST_CASE("SetGear() invalid gear (upper)")
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetGear(6) == false);
}

//SetSpeed()

TEST_CASE("SetSpeed() gear = -1; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetSpeed(10) == true);
}

TEST_CASE("SetSpeed() gear = -1; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);

	CHECK(car.SetSpeed(30) == false);
}

TEST_CASE("SetSpeed() gear = 0; speed up") //
{
	Car car;
	car.TurnOnEngine();

	CHECK(car.SetSpeed(30) == false);
}

TEST_CASE("SetSpeed() gear = 0; speed down") //
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(0);

	CHECK(car.SetSpeed(20) == true);
}

TEST_CASE("SetSpeed() gear = 1; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);

	CHECK(car.SetSpeed(30) == true);
}

TEST_CASE("SetSpeed() gear = 1; speed not in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.SetSpeed(40) == false);
}

TEST_CASE("SetSpeed() gear = 2; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetSpeed(40) == true);
}

TEST_CASE("SetSpeed() gear = 2; speed not in range (upper)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetSpeed(100) == false);
}

TEST_CASE("SetSpeed() gear = 2; speed not in range (lower)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);

	CHECK(car.SetSpeed(0) == false);
}

TEST_CASE("SetSpeed() gear = 3; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetSpeed(50) == true);
}

TEST_CASE("SetSpeed() gear = 3; speed not in range (upper)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetSpeed(100) == false);
}

TEST_CASE("SetSpeed() gear = 3; speed not in range (lower)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);

	CHECK(car.SetSpeed(0) == false);
}

TEST_CASE("SetSpeed() gear = 4; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);

	CHECK(car.SetSpeed(60) == true);
}

TEST_CASE("SetSpeed() gear = 4; speed not in range (upper)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);

	CHECK(car.SetSpeed(150) == false);
}

TEST_CASE("SetSpeed() gear = 4; speed not in range (lower)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);

	CHECK(car.SetSpeed(0) == false);
}

TEST_CASE("SetSpeed() gear = 5; speed in range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);

	CHECK(car.SetSpeed(150) == true);
}

TEST_CASE("SetSpeed() gear = 5; speed not in range (upper)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);

	CHECK(car.SetSpeed(160) == false);
}

TEST_CASE("SetSpeed() gear = 5; speed not in range (lower)")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(50);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);

	CHECK(car.SetSpeed(10) == false);
}

TEST_CASE("SetSpeed() speed < 0")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.SetSpeed(-10) == false);
}

TEST_CASE("SetSpeed() engine off")
{
	Car car;
	CHECK(car.SetSpeed(10) == false);
}
