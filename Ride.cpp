#include "Ride.h"

// Default constructor
Ride::Ride() {
    rideID = 0;
    driverID = "";
    driverName = "";
    pickupLocation = "";
    destination = "";
    departureTime = "";
    rideDate = "";
    totalSeats = 0;
    availableSeats = 0;
    fare = 0.0;
    status = "Active";
    vehicleType = "Car";
}

// Parameterized constructor
Ride::Ride(int id, string dID, string dName, string pickup, string dest,
           string time, string date, int seats, double price, string vType) {
    rideID = id;
    driverID = dID;
    driverName = dName;
    pickupLocation = pickup;
    destination = dest;
    departureTime = time;
    rideDate = date;
    totalSeats = seats;
    availableSeats = seats;
    fare = price;
    status = "Active";
    vehicleType = vType;
}

// Getters
int Ride::getRideID() const {
    return rideID;
}

string Ride::getDriverID() const {
    return driverID;
}

string Ride::getDriverName() const {
    return driverName;
}

string Ride::getPickupLocation() const {
    return pickupLocation;
}

string Ride::getDestination() const {
    return destination;
}

string Ride::getDepartureTime() const {
    return departureTime;
}

string Ride::getRideDate() const {
    return rideDate;
}

int Ride::getTotalSeats() const {
    return totalSeats;
}

int Ride::getAvailableSeats() const {
    return availableSeats;
}

double Ride::getFare() const {
    return fare;
}

string Ride::getStatus() const {
    return status;
}

string Ride::getVehicleType() const {
    return vehicleType;
}

// Book a seat if available
bool Ride::bookSeat() {
    if (availableSeats > 0 && status == "Active") {
        availableSeats = availableSeats - 1;
        return true;
    }
    return false;
}

// Book multiple seats if available
bool Ride::bookSeats(int count) {
    if (count > 0 && availableSeats >= count && status == "Active") {
        availableSeats = availableSeats - count;
        return true;
    }
    return false;
}

// Cancel a booked seat
bool Ride::cancelSeat() {
    if (availableSeats < totalSeats) {
        availableSeats = availableSeats + 1;
        return true;
    }
    return false;
}

// Update status
void Ride::setStatus(string newStatus) {
    status = newStatus;
}

// Display ride details clearly
void Ride::displayRide() const {
    cout << "  Ride ID: #" << rideID << " | " << pickupLocation << " -> " << destination << "\n";
    cout << "    Driver: " << driverName << " (" << driverID << ")\n";
    cout << "    Vehicle: " << vehicleType << "\n";
    cout << "    Date: " << rideDate << " | Time: " << departureTime << "\n";
    cout << "    Seats: " << availableSeats << " / " << totalSeats << " available\n";
    cout << "    Fare : PKR " << fare << " per seat\n";
    cout << "    Status: " << status << "\n";
    cout << "  --------------------------------------------------\n";
}
