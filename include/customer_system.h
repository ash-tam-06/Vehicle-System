# pragma once
#include <iostream>
#include <memory>
#include <map>


using namespace std;


struct Customer {
    string name;
   shared_ptr<vehicle> rentedVehicle;

    void printInfo() const {
        cout << "Name: " << name << endl;
    }
};

inline map<string, Customer> customerList;

void addCustomer(const string& name);

string validateCustomerName();


bool rentVehicle(const string& customerName, const int& regNum);

bool returnVehicle(const string& customerName);


