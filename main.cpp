//Коровашев Дмитрий 2-МД-21
//File: main.cpp

#include <iostream>
#include "Car.h"
#include "Configuration.h"
#include "Accessories.h"
#include "Deal.h"

void chooseCar(Car& car) {
    car.chooseCarModel();
    std::cout << "Модель выбрана" << std::endl;
}

void chooseAccessories(Car& car) {
    car.chooseAccessories();
    std::cout << "\nПромежуточная стоимость автомобиля с учётом дополнительных аксессуаров: " << car.getIntermediatePrice() << " Рублей" << std::endl;
}

void applyDiscountsAndLoans(Car& car) {
    car.finalizeDeal();
    car.getDeal().displayDealDetails(); 
}

void displayTotalCost(const Car& car) {
    car.displayFinalDetails();
}

void placeOrder(Car& car) {
    car.collectClientInformation();
    car.saveDealToFile(car.getFullConfiguration(), car.getSelectedAccessories());
    std::cout << "\nЗаявка отправлена!" << std::endl;  
}

void showMainMenu(Car& car) {
    int choice;
    bool exitProgram = false;
    while (!exitProgram) {
        std::cout << "\n[1] Выбрать модель автомобиля" << std::endl;
        std::cout << "[2] Выбрать дополнительные аксессуары" << std::endl;
        std::cout << "[3] Рассчитать скидки и акции" << std::endl;
        std::cout << "[4] Рассчитать итоговую стоимость" << std::endl;
        std::cout << "[5] Оставить заявку" << std::endl;
        std::cout << "[6] Закрыть конфигуратор" << std::endl;
        std::cout << "\nВведите номер пункта меню: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
            std::cout << "Ошибка, введите корректное значение от 1 до 6!" << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            chooseCar(car);
            break;
        case 2:
            if (car.canChooseAccessories()) {
                chooseAccessories(car);
            }
            else {
                std::cout << "\nСначала выберите автомобиль!" << std::endl;
            }
            break;
        case 3:
            if (car.canFinalizeDeal()) {
                applyDiscountsAndLoans(car);
            }
            else {
                std::cout << "\nСначала выберите автомобиль и аксессуары!" << std::endl;
            }
            break;
        case 4:
            if (car.canDisplayFinalDetails()) {
                displayTotalCost(car);
                std::cout << "\nХотите заполнить всё сначала? \n1 - Да, 2 - Нет" << std::endl;
                std::cout << "Ожидание ответа..." << std::endl;
                int restartChoice;
                std::cin >> restartChoice;
                if (restartChoice == 1) {
                    car.resetData();
                }
            }
            else {
                std::cout << "\nСначала выберите автомобиль, аксессуары, а также рассчитайте скидки и акции!" << std::endl;
            }
            break;
        case 5:
            if (car.canPlaceOrder()) {
                placeOrder(car);
                std::cout << "\nХотите заполнить всё сначала? \n1 - Да, 2 - Нет" << std::endl;
                std::cout << "Ожидание ответа..." << std::endl;
                int restartChoice;
                std::cin >> restartChoice;
                if (restartChoice == 1) {
                    car.resetData();
                }
            }
            else {
                std::cout << "\nСначала выполните все шаги!" << std::endl;
            }
            break;
        case 6:
            std::cout << "\nСпасибо за использование конфигуратора. До свидания!" << std::endl;
            exitProgram = true;
            break;
        default:
            std::cout << "Ошибка, введите корректное значение от 1 до 6!" << std::endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::cout << "Коровашев Дмитрий Константинович, 2-МД-21\n";
    std::cout << "Автомобильные перевозки. Отдел продаж\n\n";
    std::cout << "Добро пожаловать! Это конфигуратор автосалона Lada!\n";

    Car car;
    showMainMenu(car);

    return 0;
}
