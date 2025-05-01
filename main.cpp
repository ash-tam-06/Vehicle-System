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

void loadFromFile() {
    ifstream file("fleet.csv");
    int reg;
    int typeInt;
    bool available;
    char comma;

    while (file >> reg >> comma >> typeInt >> comma >> available) {
        addVehicle(reg, static_cast<vehicleType>(typeInt));
        fleet[reg]->available = available;
    }
    cout << "Fleet loaded from CSV.\n";
}

void menu() {
    int choice;
    cout << "Please choose an option:\n";
    cout << "1. Add vehicle\n";
    cout << "2. Rent vehicle\n";
    cout << "3. Return vehicle\n";
    cout << "4. Load fleet\n";
    cout << "5. Save fleet\n";
    cout << "9. Exit\n";
    cin >> choice;

    while (choice != 9) {
        if (choice == 1) {
            int regNum;
            int type;
            cout << "Enter vehicle reg num: ";
            cin >> regNum;
            cout << "Enter vehicle type: (0 = Car, 1 = Bike, 2 = Truck)";
            cin >> type;
            addVehicle(regNum, static_cast<vehicleType>(type));
        }else if (choice == 2) {
            string name;
            int regNum;
            cout << "Customer full name: ";
            cin >> name;
            cout << "Vehicle reg num: "; //TODO this part loops for forever if given full name
                                         //with a space
            cin >> regNum;
            rentVehicle(name, regNum);
        }else if (choice == 3) {
            string name;
            cout << "Customer full name: ";
            cin >> name;
            returnVehicle(name);
        }else if (choice == 4) {
            loadFromFile();
        } else if (choice == 5) {
            saveToFile();
        }
        cout << "Please choose an option:\n";
        cin >> choice;
    }

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

    loadFromFile();

    menu();
    return 0;
}
