#include <gtest/gtest.h>
#include <fstream>
#include "../include/vehicle_system.h"
#include "../include/customer_system.h"
#include "../include/globals.h"

// Test 1: Test adding vehicles to the fleet
TEST(VehicleTest, AddVehicleTest) {
    addVehicle(1, bike);
    ASSERT_TRUE(fleet.contains(1));
    ASSERT_EQ(fleet[1]->type, bike);
    ASSERT_TRUE(fleet[1]->available);
}

// Test 2: Test renting a vehicle
TEST(VehicleTest, RentVehicleTest) {
    addVehicle(2, car);
    addCustomer("Ash Ketchum");

    ASSERT_TRUE(rentVehicle("Ash Ketchum", 2));

    ASSERT_FALSE(fleet[1002]->available);

    ASSERT_NE(customers["Ash Ketchum"].rentedVehicle, nullptr);
    ASSERT_EQ(customers["Ash Ketchum"].rentedVehicle->regNumber, 2);
}

// Test 3: Test renting an unavailable vehicle
TEST(VehicleTest, RentUnavailableVehicleTest) {
    addVehicle(3, van);
    addCustomer("Bob Dave");

    rentVehicle("Bob Dave", 3);

    ASSERT_FALSE(rentVehicle("Bob Dave", 3));
}

// Test 4: Test returning a vehicle
TEST(VehicleTest, ReturnVehicleTest) {
    addVehicle(4, bike);
    addCustomer("Jack Smith");
    rentVehicle("Jack Smith", 4);

    returnVehicle("Jack Smith");

    ASSERT_TRUE(fleet[4]->available);


    ASSERT_EQ(customers["Jack Smith"].rentedVehicle, nullptr);
}

// Test 5: Test saving to file
TEST(FileTest, SaveToFileTest) {
    addVehicle(5, car);
    addCustomer("Karol Smith");

    rentVehicle("Karol Smith", 5);

    ASSERT_TRUE(saveToFile());


    std::ifstream fleetFile("fleet.csv");
    ASSERT_TRUE(fleetFile.is_open());


    std::ifstream customerFile("customers.dat", std::ios::binary);
    ASSERT_TRUE(customerFile.is_open());
}

// Test 6: Test loading from file
TEST(FileTest, LoadFromFileTest) {

    addVehicle(6, van);
    addCustomer("Susan Grace");
    rentVehicle("Susan Grace", 6);

    saveToFile();

    fleet.clear();
    customers.clear();

    ASSERT_TRUE(loadFromFile());

    ASSERT_TRUE(fleet.contains(6));
    ASSERT_EQ(customers["Susan Grace"].rentedVehicle->regNumber, 6);
}

// Test 7: Test invalid customer name for vehicle return
TEST(CustomerTest, InvalidCustomerReturnTest) {
    ASSERT_NO_THROW(validateReturn());
}

// Test 8: Test invalid vehicle registration number for renting
TEST(VehicleTest, InvalidVehicleRegNumTest) {
    addVehicle(7, bike);
    addCustomer("Serena Blade");

    ASSERT_FALSE(rentVehicle("Serena Blade", 99));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}