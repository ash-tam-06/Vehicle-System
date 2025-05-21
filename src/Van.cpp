#include "../include/Van.h"

Van::Van(int reg) : Vehicle(reg) {
  std::cout << "Van created" << std::endl;
}

VehicleType Van::getType() const {
  return VehicleType::van;
}