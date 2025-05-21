#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(int reg): regNumber{reg}, available{true}{}

int Vehicle::getRegNumber() const {
        return regNumber;
}

bool Vehicle::isAvailable() const {
        return available;
}

void Vehicle::setAvailable(bool available) {
        this->available = available;
}