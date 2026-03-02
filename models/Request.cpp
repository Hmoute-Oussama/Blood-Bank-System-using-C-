#include "Request.h"
#include <iostream>
using namespace std;
// implementation of the constructors :
Request::Request() : requestId(0),patientName(""),bloodType(""),quantity(0.0),urgency(Urgency::Low),status(RequestStatus::Pending),date("") {}
Request::Request(int requestId, string patientName, string bloodType, double quantity, Urgency urgency, RequestStatus status, string date) : requestId(requestId),patientName(patientName),bloodType(bloodType),quantity(quantity),urgency(urgency),status(status),date(date) {}
// implementation of the getters :
int Request::getRequestId() const {
    return requestId;
}
string Request::getPatientName() const {
    return patientName;
}
string Request::getBloodType() const {
    return bloodType;
}
double Request::getQuantity() const {
    return quantity;
}
Urgency Request::getUrgency() const {
    return urgency;
}
RequestStatus Request::getStatus() const {
    return status;
}
string Request::getDate() const {
    return date;
}
// implementation of the setters :
void Request::setRequestId(int requestId){
    this->requestId = requestId;
}
void Request::setPatientName(string patientName){
    this->patientName = patientName;
}
void Request::setBloodType(string bloodType){
    this->bloodType = bloodType;
}
void Request::setQuantity(double quantity){
    this->quantity = quantity;
}
void Request::setUrgency(Urgency urgency){
    this->urgency = urgency;
}
void Request::setStatus(RequestStatus status){
    this->status = status;
}
void Request::setDate(string date){
    this->date = date;
}
// implementation of the display function :
void Request::display() const {
    displayRequestInfo();
}
// implementation of the display function :
void Request::displayRequestInfo() const {
    cout << "────────────────────────────────" << endl;
    cout<<"Request ID: " << requestId << endl;
    cout<<"Patient Name: " << patientName << endl;
    cout<<"Blood Type: " << bloodType << endl;
    cout<<"Quantity: " << quantity << " units" << endl;
    cout<<"Urgency: " << urgencyToString() << endl;
    cout<<"Status: " << statusToString() << endl;
    cout<<"Date: " << date << endl;
}
// implementation of the urgencyToString function :
string Request::urgencyToString() const {
    switch (urgency) {
        case Urgency::Low: return "Low";
        case Urgency::Medium: return "Medium";
        case Urgency::Critical: return "Critical";
        default: return "Unknown";
    }
}
// implementation of the statusToString function :
string Request::statusToString() const {
    switch (status) {
        case RequestStatus::Pending: return "Pending";
        case RequestStatus::Fulfilled: return "Fulfilled";
        case RequestStatus::Cancelled: return "Cancelled";
        default: return "Unknown";
    }
}