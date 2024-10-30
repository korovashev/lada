//Коровашев Дмитрий 2-МД-21
//File: Configuration.cpp

#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

Configuration::Configuration() : price(0.0) {
    modelToBodyTypes = {
        {"Lada Granta", {"Седан", "Лифтбек"}},
        {"Lada Niva", {"Legend 3 дв.", "Travel", "Legend Bronto"}},
        {"Lada Vesta", {"Седан", "SW", "SW Cross"}},
        {"Lada Granta Sportline", {"Лифтбек"}}
    };

    data = {
        {"Lada Granta", {
            {"Седан", {
                {"Classic'24", {{"Серебристо-темно-серый \"Борнео\" (633) - металлик", "Золотисто-коричневый \"Кориандр\" (790) - металлик"}, 1007900}},
                {"Comfort'24", {{"Золотисто-коричневый \"Кориандр\" (790) - металлик"}, 1037900}},
                {"#Club'24", {{"Серебристо-темно-серый \"Борнео\" (633) - металлик"}, 1104900}}
            }},
            {"Лифтбек", {
                {"Classic'24", {{"Черный \"Пантера\" (672)", "Белый \"Ледниковый\" (221)", "Золотисто-коричневый \"Кориандр\" (790) - металлик", "Серебристо-темно-серый \"Борнео\" (633) - металлик"}, 1022000}},
                {"Comfort'23", {{"Серебристый \"Платина\" (691) - металлик", "Серебристо-темно-серый \"Борнео\" (633) - металлик"}, 1048000}},
                {"Comfort'24", {{"Черный \"Пантера\" (672)", "Белый \"Ледниковый\" (221)", "Серебристый \"Платина\" (691) - металлик", "Золотисто-коричневый \"Кориандр\" (790) - металлик", "Серебристо-темно-серый \"Борнео\" (633) - металлик"}, 1067900}}
            }}
        }},
        {"Lada Niva", {
            {"Legend 3 дв.", {
                {"Luxe'24", {{"Белый \"Ледниковый\" (221)"}, 1066000}},
                {"Urban'24", {{"Белый \"Ледниковый\" (221)"}, 1112000}},
                {"[Black]'24", {{"Белый \"Ледниковый\" (221)"}, 1131000}}
            }},
            {"Travel", {
                {"Classic'24", {{"Темно-зеленый \"Несси 2\" (316)", "Белый \"Ледниковый\" (221)"}, 1269900}}
            }},
            {"Legend Bronto", {
                {"Luxe'24", {{"Белый \"Ледниковый\" (221)", "Темно-зеленый \"Несси 2\" (316)"}, 1404000}},
                {"Prestige'24", {{"Белый \"Ледниковый\" (221)", "Темно-зеленый \"Несси 2\" (316)"}, 1478000}}
            }}
        }},
        {"Lada Vesta", {
            {"Седан", {
                {"Comfort'23", {{"Белый \"Ледниковый\" (221)"}, 1459900}},
                {"Comfort'24", {{"Белый \"Ледниковый\" (221)"}, 1588900}},
                {"Life'23", {{"Белый \"Ледниковый\" (221)"}, 1591900}},
                {"Enjoy", {{"Белый \"Ледниковый\" (221)"}, 1646900}},
                {"Life'24", {{"Белый \"Ледниковый\" (221)"}, 1677900}}
            }},
            {"SW", {
                {"Comfort'24", {{"Белый \"Ледниковый\" (221)", "Черный \"Пантера\" (672)"}, 1643900}},
                {"Life'24", {{"Белый \"Ледниковый\" (221)"}, 1732900}},
                {"Enjoy'24", {{"Белый \"Ледниковый\" (221)"}, 1873900}},
                {"Techno'24", {{"Черный \"Пантера\" (672)"}, 2015900}}
            }},
            {"SW Cross", {
                {"Life'24", {{"Черный \"Пантера\" (672)", "Белый \"Ледниковый\" (221)"}, 1940900}},
                {"Enjoy'24", {{"Черный \"Пантера\" (672)", "Белый \"Ледниковый\" (221)"}, 2010900}},
                {"Techno'24", {{"Черный \"Пантера\" (672)"}, 2127900}}
            }}
        }},
        {"Lada Granta Sportline", {
            {"Лифтбек", {
                {"Comfort'23", {{"Белый \"Ледниковый\" (221)", "Черный \"Пантера\" (672)"}, 1304000}}
            }}
        }}
    };
}

bool Configuration::getUserChoice(int& choice, int maxChoice) {
    std::cout << "Ожидание ответа..." << std::endl;
    std::cin >> choice;
    if (std::cin.fail() || choice < 0 || choice > maxChoice) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка, введите корректное значение!" << std::endl;
        return false;
    }
    return true;
}

bool Configuration::checkAvailability() const {
    std::ifstream infile("cars_database.txt");
    if (!infile) {
        std::cerr << "\nОшибка открытия файла базы данных!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.find(model) != std::string::npos &&
            line.find(bodyType) != std::string::npos &&
            line.find(trimLevel) != std::string::npos &&
            line.find(color) != std::string::npos) {
            if (line.find("в наличии") != std::string::npos) {
                std::cout << "\nВыбранный автомобиль в наличии" << std::endl;
                return true;
            }
            else if (line.find("под заказ") != std::string::npos) {
                std::cout << "\nАвтомобиль доступен только под заказ" << std::endl;
                return false;
            }
        }
    }

    std::cout << "\nАвтомобиль доступен только под заказ" << std::endl;
    return false;
}

void Configuration::selectConfiguration() {
    while (true) {
        while (true) {
            std::cout << "\nВыберите модель: " << std::endl;
            std::cout << "[1] Lada Granta" << std::endl;
            std::cout << "[2] Lada Granta Sportline" << std::endl;
            std::cout << "[3] Lada Niva" << std::endl;
            std::cout << "[4] Lada Vesta" << std::endl;
            int modelChoice;
            if (getUserChoice(modelChoice, static_cast<int>(modelToBodyTypes.size()))) {
                auto it = modelToBodyTypes.begin();
                std::advance(it, modelChoice - 1);
                model = it->first;
                break;
            }
        }

        while (true) {
            std::cout << "\nВыберите тип кузова: " << std::endl;
            std::cout << "[0] К выбору модели" << std::endl;
            int i = 1;
            for (const auto& bodyType : modelToBodyTypes[model]) {
                std::cout << "[" << i++ << "] " << bodyType << std::endl;
            }
            int bodyChoice;
            if (getUserChoice(bodyChoice, static_cast<int>(modelToBodyTypes[model].size()))) {
                if (bodyChoice == 0) {
                    model.clear();
                    break;
                }
                auto it = modelToBodyTypes[model].begin();
                std::advance(it, bodyChoice - 1);
                bodyType = *it;
                break;
            }
        }

        if (model.empty()) continue;

        while (true) {
            std::cout << "\nВыберите комплектацию: " << std::endl;
            std::cout << "[0] К выбору модели" << std::endl;
            int i = 1;
            for (const auto& pair : data[model][bodyType]) {
                std::cout << "[" << i++ << "] " << pair.first << std::endl;
            }
            int trimChoice;
            if (getUserChoice(trimChoice, static_cast<int>(data[model][bodyType].size()))) {
                if (trimChoice == 0) {
                    bodyType.clear();
                    break;
                }
                auto it = data[model][bodyType].begin();
                std::advance(it, trimChoice - 1);
                trimLevel = it->first;
                break;
            }
        }

        if (bodyType.empty()) continue;

        while (true) {
            std::cout << "\nВыберите цвет: " << std::endl;
            std::cout << "[0] К выбору модели" << std::endl;
            int i = 1;
            for (const auto& color : data[model][bodyType][trimLevel].first) {
                std::cout << "[" << i++ << "] " << color << std::endl;
            }
            int colorChoice;
            if (getUserChoice(colorChoice, static_cast<int>(data[model][bodyType][trimLevel].first.size()))) {
                if (colorChoice == 0) {
                    trimLevel.clear();
                    break;
                }
                auto it = data[model][bodyType][trimLevel].first.begin();
                std::advance(it, colorChoice - 1);
                color = *it;
                break;
            }
        }

        if (trimLevel.empty()) continue;

        displayFullModelName();
        price = data[model][bodyType][trimLevel].second;
        displaySelectedConfiguration();

        checkAvailability();

        break;
    }
}

double Configuration::getPrice() const {
    return price;
}

void Configuration::displaySelectedConfiguration() const {
    std::cout << "\nВыбранная конфигурация:" << std::endl;
    std::cout << "Модель: " << model << std::endl;
    std::cout << "Тип кузова: " << bodyType << std::endl;
    std::cout << "Комплектация: " << trimLevel << std::endl;
    std::cout << "Цвет: " << color << std::endl;
    std::cout << "\nЦена: " << std::fixed << std::setprecision(0) << price << " Рублей" << std::endl;
}

void Configuration::displayFullModelName() const {
    std::cout << "\nВы выбрали: " << model << " " << bodyType << " " << trimLevel << " " << color << std::endl;
}

std::string Configuration::getModel() const {
    return model;
}

std::string Configuration::getBodyType() const {
    return bodyType;
}

std::string Configuration::getTrimLevel() const {
    return trimLevel;
}

std::string Configuration::getColor() const {
    return color;
}
