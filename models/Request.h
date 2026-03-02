#include<string>
#pragma once
using namespace std;
enum class Urgency{
    Low,
    Medium,
    Critical
};
enum class RequestStatus{
    Pending,
    Fulfilled,
    Cancelled
};
class Request{
private:
    int requestId;
    std::string patientName;
    std::string bloodType;
    double quantity;          
    Urgency urgency;
    RequestStatus status;
    std::string date;
public:
// constructors :
    Request();
    Request(int requestId, string patientName, string bloodType, double quantity, Urgency urgency, RequestStatus status, string date);
// getters :
    int getRequestId() const;
    string getPatientName() const;
    string getBloodType() const;
    double getQuantity() const;
    Urgency getUrgency() const;
    RequestStatus getStatus() const;
    string getDate() const;
// setters :
    void setRequestId(int requestId);
    void setPatientName(string patientName);
    void setBloodType(string bloodType);
    void setQuantity(double quantity);
    void setUrgency(Urgency urgency);
    void setStatus(RequestStatus status);
    void setDate(string date);
    void display() const;
    void displayRequestInfo() const;
    string urgencyToString() const;
    string statusToString() const;
};