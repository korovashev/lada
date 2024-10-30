//Коровашев Дмитрий 2-МД-21
//File: Accessories.h

#ifndef ACCESSORIES_H
#define ACCESSORIES_H

#include <string>
#include <list>
#include <iostream>
#include <iomanip>

struct Accessory {
    std::string name;
    double price;
};

class Accessories {
private:
    std::list<Accessory> availableAccessories;
    std::list<Accessory> selectedAccessories;
    double basePrice;

    bool getUserChoice(int& choice, int maxChoice);
    bool getUserChoice(int& choice, int maxChoice, bool allowBack);

public:
    Accessories();
    void selectAccessories();
    double getTotalAccessoriesPrice() const;
    void displaySelectedAccessories() const;
    void setBasePrice(double price);
    std::list<Accessory> getSelectedAccessories() const;
};

#endif 