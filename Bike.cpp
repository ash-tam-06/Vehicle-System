//
// Created by Asmita Tamang on 5/20/25.
//

#include "Bike.h"

Bike::Bike(int reg) : Vehicle(reg) {
  std::cout << "Bike made" << std::endl;
}

VehicleType Bike::getType() const {
  return bike;
}
