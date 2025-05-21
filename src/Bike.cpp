#include "../include/Bike.h"

Bike::Bike(int reg) : Vehicle(reg) {
  if (reg < 0) throw std::invalid_argument("Registration number cannot be negative.");
  std::cout << "Bike made" << std::endl;
}

VehicleType Bike::getType() const {
  return bike;
}
