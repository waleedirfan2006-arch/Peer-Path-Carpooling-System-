#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <string>

using namespace std;

// Represents a carpool ride offered by a student or faculty driver
class Ride {
private:
    int rideID;               // Unique ID for the ride (e.g., 101, 102)
    string driverID;          // Roll number or employee ID of driver
    string driverName;        // Driver's full name
    string pickupLocation;    // Starting point (e.g., "Johar Chowrangi")
    string destination;       // End point (e.g., "NED Main Campus")
    string departureTime;     // Time of departure (e.g., "07:30 AM")
    string rideDate;          // Date of travel (e.g., "2026-10-20")
    int totalSeats;           // Total passenger capacity
    int availableSeats;       // Number of seats currently empty
    double fare;              // Fuel share contribution per seat in PKR
    string status;            // "Active", "Completed", or "Cancelled"
    string vehicleType;       // Type of vehicle (e.g., "Car", "Bike")

public:
    // Default constructor
    Ride();

    // Parameterized constructor
    Ride(int id, string dID, string dName, string pickup, string dest,
         string time, string date, int seats, double price, string vType = "Car");

    // Getters
    int getRideID() const;
    string getDriverID() const;
    string getDriverName() const;
    string getPickupLocation() const;
    string getDestination() const;
    string getDepartureTime() const;
    string getRideDate() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;
    double getFare() const;
    string getStatus() const;
    string getVehicleType() const;

    // Actions
    bool bookSeat();                  // Decreases available seats by 1
    bool bookSeats(int count);        // Decreases available seats by count
    bool cancelSeat();                // Increases available seats by 1
    void setStatus(string newStatus);

    // Display
    void displayRide() const;
};

#endif
