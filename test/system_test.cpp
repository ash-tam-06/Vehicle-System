#include <gtest/gtest.h>
#include "../include/FleetManager.h"
#include "../include/Vehicle.h"
#include "../include/Bike.h"
#include "../include/Car.h"
#include "../include/Van.h"


TEST(VehicleTest, BikeCreation) {
    Bike bike(77);
    EXPECT_EQ(bike.getRegNumber(), 77);
    EXPECT_TRUE(bike.isAvailable());
    EXPECT_EQ(bike.getType(), VehicleType::bike);
}

TEST(VehicleTest, CarCreation) {
    Car car(55);
    EXPECT_EQ(car.getRegNumber(), 55);
    EXPECT_TRUE(car.isAvailable());
    EXPECT_EQ(car.getType(), VehicleType::car);
}

TEST(VehicleTest, VanCreation) {
    Van van(666);
    EXPECT_EQ(van.getRegNumber(), 666);
    EXPECT_TRUE(van.isAvailable());
    EXPECT_EQ(van.getType(), VehicleType::van);
}

TEST(VehicleTest, AvailabilityChange) {
    Bike bike(33);
    EXPECT_TRUE(bike.isAvailable());
    bike.setAvailable(false);
    EXPECT_FALSE(bike.isAvailable());
}

TEST(CustomerTest, RentAndReturnVehicle) {
    Customer person("Ash Ketchum");
    auto vehicle = std::make_shared<Car>(1);

    EXPECT_FALSE(person.hasVehicle());

    person.rentVehicle(vehicle);
    EXPECT_TRUE(person.hasVehicle());
    EXPECT_EQ(person.getVehicle()->getRegNumber(), 1);
    EXPECT_FALSE(vehicle->isAvailable());

    person.returnVehicle();
    EXPECT_FALSE(person.hasVehicle());
    EXPECT_TRUE(vehicle->isAvailable());
}

TEST(FleetManagerTest, ReturnVehicleFailWhenNoneRented) {
    FleetManager manager;
    manager.addCustomer("Ash");

    EXPECT_THROW(manager.returnVehicle("Ash"), std::logic_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}