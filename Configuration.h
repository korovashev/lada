//Коровашев Дмитрий 2-МД-21
//File: Configuration.h

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <list>
#include <map>

class Configuration {
private:
    std::string model;
    std::string bodyType;
    std::string trimLevel;
    std::string color;
    double price;

    std::map<std::string, std::map<std::string, std::map<std::string, std::pair<std::list<std::string>, double>>>> data;
    std::map<std::string, std::list<std::string>> modelToBodyTypes;

    bool getUserChoice(int& choice, int maxChoice);

public:
    Configuration();
    void selectConfiguration();
    double getPrice() const;
    void displaySelectedConfiguration() const;
    void displayFullModelName() const;

    std::string getModel() const;
    std::string getBodyType() const;
    std::string getTrimLevel() const;
    std::string getColor() const;
    bool checkAvailability() const;
};

#endif 
