//Коровашев Дмитрий 2-МД-21
//File: Deal.cpp

#include "Deal.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <regex>
#include <iomanip>

Deal::Deal() : basePrice(0.0), finalPrice(0.0), discountAmount(0.0), loanAmount(0.0), monthlyPayment(0.0), totalPayment(0.0), overpayment(0.0), isLoan(false), isFirstCar(false), isEligibleForDiscount(false) {}

void Deal::setBasePrice(double price) {
    basePrice = price;
    finalPrice = price;
}

bool Deal::getUserChoice(int& choice, int maxChoice) {
    std::cout << "Ожидание ответа..." << std::endl;
    std::cin >> choice;
    if (std::cin.fail() || choice < 1 || choice > maxChoice) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите корректное значение!" << std::endl;
        return false;
    }
    return true;
}

bool Deal::getDoubleInput(double& input) {
    std::cout << "Ожидание ответа..." << std::endl;
    std::cin >> input;
    if (std::cin.fail() || input < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите корректное значение!" << std::endl;
        return false;
    }
    return true;
}

bool Deal::getIntInput(int& input) {
    std::cout << "Ожидание ответа..." << std::endl;
    std::cin >> input;
    if (std::cin.fail() || input < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите корректное значение!" << std::endl;
        return false;
    }
    return true;
}

bool Deal::getPhoneNumberInput(std::string& input) {
    std::getline(std::cin >> std::ws, input); 
    std::regex phoneRegex(R"(\+7 \(\d{3}\) \d{3}-\d{2}-\d{2})");
    if (std::regex_match(input, phoneRegex)) {
        return true;
    }
    else {
        std::cout << "Ошибка, введите номер телефона в правильном формате!" << std::endl;
        return false;
    }
}

void Deal::applyDiscounts() {
    discountAmount = 0.0;
    while (true) {
        std::cout << "\nЭто ваш первый автомобиль? \n1 - Да, 2 - Нет:" << std::endl;
        int choice;
        if (getUserChoice(choice, 2)) {
            if (choice == 1) {
                isFirstCar = true;
                discountAmount += basePrice * 0.20;
            }
            break;
        }
    }

    if (isLoan) {
        while (true) {
            std::cout << "\nВы являетесь учителем, медработником или военнослужащим? \n1 - Да, 2 - Нет:" << std::endl;
            int choice;
            if (getUserChoice(choice, 2)) {
                if (choice == 1) {
                    isEligibleForDiscount = true;
                    discountAmount += basePrice * 0.20;
                }
                break;
            }
        }
    }

    finalPrice = basePrice - discountAmount;
}

void Deal::calculateLoanDetails() {
    std::cout << "\nВведите срок кредита в месяцах (от 12 до 120): " << std::endl;
    int loanTerm;
    while (true) {
        if (getIntInput(loanTerm) && loanTerm >= 12 && loanTerm <= 120) {
            break;
        }
        else {
            std::cout << "Ошибка, введите корректное значение от 12 до 120!" << std::endl;
        }
    }

    double annualInterestRate = 0.15;
    double monthlyInterestRate = annualInterestRate / 12;
    loanAmount = finalPrice;
    monthlyPayment = loanAmount * monthlyInterestRate / (1 - std::pow(1 + monthlyInterestRate, -loanTerm));
    totalPayment = monthlyPayment * loanTerm;
    overpayment = totalPayment - loanAmount;
    finalPrice = loanAmount - discountAmount; 
}

void Deal::finalizeDeal() {
    while (true) {
        std::cout << "\nСпособ оплаты? \n1 - Наличные, 2 - Кредит:" << std::endl;
        int choice;
        if (getUserChoice(choice, 2)) {
            if (choice == 1) {
                isLoan = false;
            }
            else if (choice == 2) {
                isLoan = true;
                calculateLoanDetails();
            }
            break;
        }
    }

    applyDiscounts();
}

void Deal::displayDealDetails() const {
    std::cout << "\nРазмер скидки: " << std::fixed << std::setprecision(0) << discountAmount << " Рублей" << std::endl;
    std::cout << "\nИтоговая цена с учётом всех скидок и условий: " << std::fixed << std::setprecision(0) << finalPrice << " Рублей" << std::endl;

    if (isLoan) {
        std::cout << "\nУсловия кредита:" << std::endl;
        std::cout << "Ежемесячный платеж: " << std::fixed << std::setprecision(0) << monthlyPayment << " Рублей" << std::endl;
        std::cout << "Переплата: " << std::fixed << std::setprecision(0) << overpayment << " Рублей" << std::endl;
    }
}

void Deal::collectClientInformation() {
    std::cout << "\nПожалуйста, введите Ваше имя: " << std::endl;
    std::getline(std::cin >> std::ws, clientName); 

    while (true) {
        std::cout << "\nВведите Ваш номер телефона в формате +7 (xxx) xxx-xx-xx: " << std::endl;
        if (getPhoneNumberInput(clientPhoneNumber)) {
            break;
        }
    }
}

void Deal::saveDealToFile(const std::string& config, const std::string& accessories) const {
    std::ofstream outFile("orders_database.txt", std::ios_base::app);
    if (outFile.is_open()) {
        outFile << "Имя клиента: " << clientName << std::endl;
        outFile << "Номер телефона: " << clientPhoneNumber << "\n" << std::endl;
        outFile << config << std::endl;
        outFile << accessories << std::endl;
        outFile << "Итоговая цена: " << std::fixed << std::setprecision(0) << finalPrice << " Рублей" << std::endl;
        outFile << "Размер скидки: " << std::fixed << std::setprecision(0) << discountAmount << " Рублей" << std::endl;
        if (isLoan) {
            outFile << "\nЕжемесячный платеж: " << std::fixed << std::setprecision(0) << monthlyPayment << " Рублей" << std::endl;
            outFile << "Переплата: " << std::fixed << std::setprecision(0) << overpayment << " Рублей" << std::endl;
        }
        outFile << "-----------------------------------" << std::endl;
        outFile.close();
    }
    else {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
    }
}

double Deal::getFinalPrice() const {
    return finalPrice;
}

void Deal::reset() {
    basePrice = 0.0;
    finalPrice = 0.0;
    discountAmount = 0.0;
    loanAmount = 0.0;
    monthlyPayment = 0.0;
    totalPayment = 0.0;
    overpayment = 0.0;
    isLoan = false;
    isFirstCar = false;
    isEligibleForDiscount = false;
    clientName.clear();
    clientPhoneNumber.clear();
}
