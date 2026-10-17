#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>

using namespace std;

// ---------- Student Model ----------
class Student {
private:
    string studentID;     // NED Roll Number or Faculty ID (e.g., CS-024)
    string studentName;   // Full name
    string department;    // Department (e.g., Computer Science)
    string email;         // University email address
    string phoneNumber;   // Contact phone number
    string role;          // "Student" or "Faculty"

public:
    // Default constructor
    Student() {
        studentID = "";
        studentName = "";
        department = "";
        email = "";
        phoneNumber = "";
        role = "Student";
    }

    // Parameterized constructor
    Student(string id, string name, string dept, string mail, string phone, string userRole) {
        studentID = id;
        studentName = name;
        department = dept;
        email = mail;
        phoneNumber = phone;
        role = userRole;
    }

    // Getters
    string getStudentID() const { return studentID; }
    string getStudentName() const { return studentName; }
    string getDepartment() const { return department; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }
    string getRole() const { return role; }

    // Display student details
    void displayStudent() const {
        cout << "  --------------------------------------------------\n";
        cout << "  ID / Roll No : " << studentID << " (" << role << ")\n";
        cout << "  Name         : " << studentName << "\n";
        cout << "  Department   : " << department << "\n";
        cout << "  Email        : " << email << "\n";
        cout << "  Phone        : " << phoneNumber << "\n";
        cout << "  --------------------------------------------------\n";
    }
};

// ---------- Ride Model ----------
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
    Ride() {
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
    Ride(int id, string dID, string dName, string pickup, string dest,
         string time, string date, int seats, double price, string vType = "Car") {
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
    int getRideID() const { return rideID; }
    string getDriverID() const { return driverID; }
    string getDriverName() const { return driverName; }
    string getPickupLocation() const { return pickupLocation; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    string getRideDate() const { return rideDate; }
    int getTotalSeats() const { return totalSeats; }
    int getAvailableSeats() const { return availableSeats; }
    double getFare() const { return fare; }
    string getStatus() const { return status; }
    string getVehicleType() const { return vehicleType; }

    // Actions
    bool bookSeat() {
        if (availableSeats > 0 && status == "Active") {
            --availableSeats;
            return true;
        }
        return false;
    }

    bool bookSeats(int count) {
        if (count > 0 && availableSeats >= count && status == "Active") {
            availableSeats -= count;
            return true;
        }
        return false;
    }

    bool cancelSeat() {
        if (availableSeats < totalSeats) {
            ++availableSeats;
            return true;
        }
        return false;
    }

    void setStatus(string newStatus) { status = newStatus; }

    // Display ride details
    void displayRide() const {
        cout << "  Ride ID: #" << rideID << " | " << pickupLocation << " -> " << destination << "\n";
        cout << "    Driver: " << driverName << " (" << driverID << ")\n";
        cout << "    Vehicle: " << vehicleType << "\n";
        cout << "    Date: " << rideDate << " | Time: " << departureTime << "\n";
        cout << "    Seats: " << availableSeats << " / " << totalSeats << " available\n";
        cout << "    Fare : PKR " << fare << " per seat\n";
        cout << "    Status: " << status << "\n";
        cout << "  --------------------------------------------------\n";
    }
};

// ---------- BookingRequest Model ----------
struct BookingRequest {
    int requestID;          // Unique request ID (e.g. 1, 2, 3...)
    int rideID;             // ID of the ride being requested
    string studentID;       // Passenger's student / roll number
    string studentName;     // Passenger's name
    string driverID;        // Driver's student / employee ID
    string pickupLocation;  // Ride pickup location
    string destination;     // Ride destination
    int requestedSeats;     // Number of seats requested
    string status;          // "Pending", "Accepted", or "Rejected"

    // Default constructor
    BookingRequest() {
        requestID = 0;
        rideID = 0;
        studentID = "";
        studentName = "";
        driverID = "";
        pickupLocation = "";
        destination = "";
        requestedSeats = 0;
        status = "Pending";
    }

    // Parameterized constructor
    BookingRequest(int reqID, int rID, string sID, string sName, string dID,
                   string pickup, string dest, int seats) {
        requestID = reqID;
        rideID = rID;
        studentID = sID;
        studentName = sName;
        driverID = dID;
        pickupLocation = pickup;
        destination = dest;
        requestedSeats = seats;
        status = "Pending";
    }

    // Display request summary
    void displayRequest() const {
        cout << "  --------------------------------------------------\n";
        cout << "  Request ID     : #" << requestID << " [" << status << "]\n";
        cout << "  Ride ID        : #" << rideID << " (" << pickupLocation << " -> " << destination << ")\n";
        cout << "  Passenger      : " << studentName << " (ID: " << studentID << ")\n";
        cout << "  Seats Requested: " << requestedSeats << "\n";
        cout << "  --------------------------------------------------\n";
    }
};

#endif // MODELS_H
