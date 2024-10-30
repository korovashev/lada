//Коровашев Дмитрий 2-МД-21
//File: Car.h

#ifndef CAR_H
#define CAR_H

#include "Configuration.h"
#include "Accessories.h"
#include "Deal.h"

class Car {
private:
    Configuration configuration;
    Accessories accessories;
    Deal deal;
    bool carChosen;
    bool accessoriesChosen;
    bool discountsApplied;

public:
    Car() : carChosen(false), accessoriesChosen(false), discountsApplied(false) {}

    void chooseConfiguration();
    void chooseAccessories();
    void finalizeDeal();
    void displayFinalDetails() const;
    void collectClientInformation();
    void saveDealToFile(const std::string& config, const std::string& accessories) const;
    std::string getFullConfiguration() const;
    std::string getSelectedAccessories() const;
    double getIntermediatePrice() const;
    bool canChooseAccessories() const { return carChosen; }
    bool canFinalizeDeal() const { return carChosen && accessoriesChosen; }
    bool canDisplayFinalDetails() const { return carChosen && accessoriesChosen && discountsApplied; }
    bool canPlaceOrder() const { return carChosen && accessoriesChosen && discountsApplied; }
    void resetData();
    Deal& getDeal() { return deal; }
    void chooseCarModel();  \
};

#endif 
