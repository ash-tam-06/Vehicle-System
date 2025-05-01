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

bool rentVehicle(const string& customerName, const int& regNum) {
    if (!fleet.contains(regNum) || !fleet[regNum]->available) {
        cout << "Vehicle unavailable." << endl;
        return false;
    }
    const auto sharedVehicle = shared_ptr<vehicle>(fleet[regNum].get(), [](vehicle*) {
        // Empty deleter since fleet owns the memory
    });
    fleet[regNum]->available = false;
    customers[customerName].rentedVehicle = sharedVehicle;
    cout << customerName << " rented: " << regNum << endl;
    return true;
}

void returnVehicle(const string& customerName) {
    if (customers[customerName].rentedVehicle != nullptr) {
        customers[customerName].rentedVehicle->available = true;
        customers[customerName].rentedVehicle = nullptr;
        std::cout << customerName << " returned their vehicle.\n";
    } else {
        std::cout << "No vehicle to return.\n";
    }
};

bool saveToFile(/*fleet*/) {
    fstream file;
    file.open("fleet.csv", ios::in | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "Failed to open file " << endl;
        return false;
    }
    file.seekg(0, ios::end);
    for (const auto& pair : fleet) {
        file << pair.first << "," << static_cast<int>(pair.second->type) << "," << pair.second->available << "\n";
    }
    file.close();
}

void loadFromFile(const string& filename) {
    ifstream file(filename);
    file.open("fleet.csv");
    if(file.is_open()) {
        string str;
        getline(file, str);
        cout<< str << '\n';
        while(!file.eof()) {
            getline(file, str, ',');
            if(str.empty()) continue;
            vehicle vehicle;
            vehicle.regNumber = stoi(str);

            getline(file, str, ',');
            vehicle.type = static_cast<vehicleType>(stoi(str));

            getline(file, str);
            vehicle.available = stoi(str);

            cout << vehicle.regNumber << '\n';
            cout << vehicle.available << '\n';
            cout << vehicle.type << "\n";
        }
    }

    file.close();

}

int main(){

    vehicle vehicle{bike,  12, true};

    //vehicle.printInfo();

    addVehicle(12, bike);

    saveToFile();
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

    saveToFile();

    loadFromFile("fleet.csv");


    return 0;
}
