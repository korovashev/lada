//Коровашев Дмитрий 2-МД-21
//File: Accessories.cpp

#include "Accessories.h"

Accessories::Accessories() : basePrice(0.0) {
    availableAccessories = {
        {"Автомобильная магнитола 1DIN PIONEER MVH-29BT", 21075},
        {"Ковры салона (литьевые, оригинальный рисунок)", 4033},
        {"Охранная система с двухсторонней связью с CAN/LIN шиной SCHER-KHAN MOBILCAR 1", 21825},
        {"Система помощи при парковке AVILINE MP-216LED-F4BU (4 чёрных датчика)", 10760},
        {"Видеорегистратор скрытой установки AVILINE DVR-B", 24581},
        {"Крепление на багажник для перевозки велосипеда (алюминиевое)", 10039},
        {"Удерживающее устройство для детей lada 001 (0+)", 7141},
        {"Аэродинамический бокс на крышу (чёрное тиснение)", 37819},
        {"Керамическое покрытие: PROFI (LADA)", 11518},
        {"Ящик-органайзер в багажник автомобиля", 5290},
        {"Крепление на багажник для перевозки лыж (4 пары) и сноуборда (2 пары)", 10520}
    };
}

bool Accessories::getUserChoice(int& choice, int maxChoice, bool allowBack) {
    std::cout << "\nОжидание ответа..." << std::endl;
    std::cin >> choice;
    if (std::cin.fail() || choice < (allowBack ? 0 : 1) || choice > maxChoice) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите корректное значение!" << std::endl;
        return false;
    }
    return true;
}

void Accessories::selectAccessories() {
    while (true) {
        auto it = availableAccessories.begin();
        int index = 1;
        selectedAccessories.clear();
        while (it != availableAccessories.end()) {
            std::cout << "\nХотите дополнительно приобрести: " << it->name << " (" << it->price << " Рублей)? \n";
            if (index > 1) {
                std::cout << "0 - Назад, ";
            }
            std::cout << "1 - Да, 2 - Нет: ";
            int choice;
            if (getUserChoice(choice, 2, index > 1)) {
                if (choice == 1) {
                    selectedAccessories.push_back(*it);
                }
                if (choice == 0 && index > 1) {
                    --it;
                    --index;
                    selectedAccessories.pop_back();
                    continue;
                }
                ++it;
                ++index;
            }
        }

        displaySelectedAccessories();

        break;
    }
}

double Accessories::getTotalAccessoriesPrice() const {
    double total = 0.0;
    for (const auto& accessory : selectedAccessories) {
        total += accessory.price;
    }
    return total;
}

void Accessories::displaySelectedAccessories() const {
    std::cout << "\nВыбранные аксессуары:" << std::endl;
    if (selectedAccessories.empty()) {
        std::cout << "Без дополнительных аксессуаров" << std::endl;
    }
    else {
        for (const auto& accessory : selectedAccessories) {
            std::cout << accessory.name << " - " << accessory.price << " Рублей" << std::endl;
        }
        std::cout << "\nОбщая стоимость аксессуаров: " << std::fixed << std::setprecision(0) << getTotalAccessoriesPrice() << " Рублей" << std::endl;
    }
}

void Accessories::setBasePrice(double price) {
    basePrice = price;
}

std::list<Accessory> Accessories::getSelectedAccessories() const {
    return selectedAccessories;
}
