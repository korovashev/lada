//Коровашев Дмитрий 2-МД-21
//File: Deal.h

#ifndef DEAL_H
#define DEAL_H

#include <string>

class Deal {
private:
    double basePrice;
    double finalPrice;
    double discountAmount;
    double loanAmount;
    double monthlyPayment;
    double totalPayment;
    double overpayment;
    bool isLoan;
    bool isFirstCar;
    bool isEligibleForDiscount;
    std::string clientName;
    std::string clientPhoneNumber;

    bool getUserChoice(int& choice, int maxChoice);
    bool getDoubleInput(double& input);
    bool getIntInput(int& input);
    bool getPhoneNumberInput(std::string& input);

public:
    Deal();
    void setBasePrice(double price);
    void applyDiscounts();
    void calculateLoanDetails();
    void finalizeDeal();
    void displayDealDetails() const;
    void collectClientInformation();
    void saveDealToFile(const std::string& config, const std::string& accessories) const;
    double getFinalPrice() const;
    void reset(); 
};

#endif 