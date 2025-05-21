#include "../include/Van.h"

Van::Van(int reg) : Vehicle(reg) {
  if (reg < 0) throw std::invalid_argument("Registration number cannot be negative.");
  std::cout << "Van created" << std::endl;
}

VehicleType Van::getType() const {
  return VehicleType::van;
}