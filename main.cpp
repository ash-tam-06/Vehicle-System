#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;


enum vehicleType {bike, car, van};
struct vehicle {
    vehicleType type;
    // double price;
    int regNumber;
    bool available;

    void printInfo() {
        cout << "Registration Number: "<< regNumber << endl;
        cout << "Vehicle type: " <<(type == bike ? "Bike" : type == car ? "Car" : "Van") << endl;
        //cout << "Price: " << price << endl;
        cout << "Available: " << (available == true ? "Available" : "Rented" ) << endl;
    }
};

struct Customer {
    string name;
    shared_ptr<vehicle> rentedVehicle;
};


map<string, Customer> customers;
unordered_map<int, unique_ptr<vehicle>> fleet;

void addVehicle(const int regNum, const vehicleType type) {
    fleet[regNum] = make_unique<vehicle>(vehicle{type, regNum, true});
}

void addCustomer(const string& name) {
    customers[name] = Customer{name,nullptr};
}

void rentVehicle(const string& customerName, const int& regNum) {
    if (!fleet.contains(regNum) || !fleet[regNum]->available) {
        std::cout << "Vehicle unavailable.\n";
        return;
    }

    const auto sharedVehicle = shared_ptr<vehicle>(fleet[regNum].get(), [](vehicle*) {
        // Empty deleter since fleet owns the memory
    });

    fleet[regNum]->available = false;
    customers[customerName].rentedVehicle = sharedVehicle;

    std::cout << customerName << " rented " << regNum << "\n";
}

//TODO
void returnVehicle(const string& customerName) {
    if (customers[customerName].rentedVehicle != nullptr) {
        customers[customerName].rentedVehicle->available = true;
        customers[customerName].rentedVehicle = nullptr;
        std::cout << customerName << " returned their vehicle.\n";
    } else {
        std::cout << "No vehicle to return.\n";
    }
};

int main() {

    vehicle vehicle{bike,  12, true};

    //vehicle.printInfo();

    addVehicle(12, bike);
    addVehicle(13, car);

    for (const auto& type : fleet) {
        fleet[type.first]->printInfo();
    }

    addCustomer("Eli Smith");
    addCustomer("Adam Red");

    for (const auto& person : customers) {
        cout << person.first << endl;
    }

    rentVehicle("Eli Smith", 12);
    rentVehicle("Adam Red", 10);
    rentVehicle("Adam Red", 13);
    returnVehicle("Eli Smith");
    returnVehicle("Adam Red");
    returnVehicle("Eli Smith");

    return 0;
}
