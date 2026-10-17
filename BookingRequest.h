#ifndef BOOKINGREQUEST_H
#define BOOKINGREQUEST_H

#include <iostream>
#include <string>

using namespace std;

// Represents a passenger's request to book seat(s) on a carpool ride
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

#endif
