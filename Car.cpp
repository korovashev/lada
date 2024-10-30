//Коровашев Дмитрий 2-МД-21
//File: Car.cpp

#include "Car.h"
#include <iostream>
#include <sstream>

void Car::chooseConfiguration() {
    configuration.selectConfiguration();
    carChosen = true;
}

void Car::chooseAccessories() {
    accessories.selectAccessories();
    accessoriesChosen = true;
}

void Car::finalizeDeal() {
    deal.setBasePrice(configuration.getPrice() + accessories.getTotalAccessoriesPrice());
    deal.finalizeDeal();
    discountsApplied = true;
}

void Car::displayFinalDetails() const {
    configuration.displaySelectedConfiguration();
    accessories.displaySelectedAccessories();
    deal.displayDealDetails();
}

void Car::collectClientInformation() {
    deal.collectClientInformation();
}

void Car::saveDealToFile(const std::string& config, const std::string& accessories) const {
    deal.saveDealToFile(config, accessories);
}

std::string Car::getFullConfiguration() const {
    std::ostringstream oss;
    oss << "Модель: " << configuration.getModel() << "\n"
        << "Тип кузова: " << configuration.getBodyType() << "\n"
        << "Комплектация: " << configuration.getTrimLevel() << "\n"
        << "Цвет: " << configuration.getColor() << "\n";
    return oss.str();
}

std::string Car::getSelectedAccessories() const {
    const auto& selectedAccessories = accessories.getSelectedAccessories();
    if (selectedAccessories.empty()) {
        return "Дополнительные аксессуары не выбраны";
    }

    std::ostringstream oss;
    for (const auto& accessory : selectedAccessories) {
        oss << accessory.name << " - " << accessory.price << " Рублей\n";
    }
    return oss.str();
}

double Car::getIntermediatePrice() const {
    return configuration.getPrice() + accessories.getTotalAccessoriesPrice();
}

void Car::resetData() {
    configuration = Configuration();
    accessories = Accessories();
    deal.reset();
    carChosen = false;
    accessoriesChosen = false;
    discountsApplied = false;
}

void Car::chooseCarModel() {
    chooseConfiguration();
}
