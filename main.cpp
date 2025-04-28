#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;


enum vehicleType {bike, car, van};
struct vehicle {
    vehicleType type;
    double price;
    int regNumber;
    bool available;

    void printInfo() {
        cout << "Registration Number: "<< regNumber << endl;
        cout << "Vehicle type: " <<(type == bike ? "Bike" : type == car ? "Car" : "Van") << endl;
        cout << "Price: " << price << endl;
        cout << "Available: " << (available == true ? "Available" : "Rented" ) << endl;
    }
};

struct Customer {
    string name;
    shared_ptr<vehicle> rentedVehicle;
};


map<string, Customer> customers;
unordered_map<int, unique_ptr<vehicle>> fleet;

void addVehicle(int regNum, vehicleType type, double price) {
    fleet[regNum] = make_unique<vehicle>(vehicle{type,price, regNum, true});
}

void addCustomer(string name) {
    customers[name] = Customer{name,nullptr};
}

//TODO
void rentVehicle(){}
void returnVehicle(){};

int main() {

    vehicle vehicle{bike, 20.50, 12, true};

    //vehicle.printInfo();

    addVehicle(12, bike, 20.50);
    addVehicle(13, car, 30.5);

    for (const auto& type : fleet) {
        fleet[type.first]->printInfo();
    }

    addCustomer("Eli Smith");
    addCustomer("Adam Red");

    for (const auto& person : customers) {
        cout << person.first << endl;
    }

    return 0;
}
