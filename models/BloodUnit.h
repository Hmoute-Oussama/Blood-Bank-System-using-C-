#pragma once
#include <string>
using namespace std;
class BloodUnit{
private:
    int unitId;
    string bloodType;
    int donorId;
    string donationDate;
    string expiryDate;
    double quantity;
public:
//constructors :
    BloodUnit();
    BloodUnit(int unitId,string bloodType,int donorId,string donationDate,string expiryDate,double quantity);
//getters :
int getUnitId() const;
string getBloodType() const;
int getDonorId() const;
string getDonationDate() const;
string getCollectionDate() const;
string getExpiryDate() const;
double getQuantity() const;
//setters :
void setUnitId(int unitId);
void setBloodType(string bloodType);
void setDonorId(int donorId);
void setDonationDate(string donationDate);
void setExpiryDate(string expiryDate);
void setQuantity(double quantity);
bool isExpired(const string& currentDate) const;
void displayBloodUnitInfo() const;
};