#ifndef CARPOOLSYSTEM_H
#define CARPOOLSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Student.h"
#include "Ride.h"
#include "BookingRequest.h"
#include "CampusGraph.h"

using namespace std;

// Main system controller managing users, rides, and menu choices
class CarpoolSystem {
private:
    vector<Student> students;          // Dynamic list of registered students and faculty
    vector<Ride> rides;                // Dynamic list of all carpool rides
    vector<BookingRequest> allRequests;// Master list of all booking requests
    CampusGraph campusGraph;           // Campus transit network graph (DSA Graph, BFS & Dijkstra)
    int nextRideID;                    // Next unique ride ID
    int nextRequestID;                 // Next unique booking request ID
    string loggedInStudentID;          // ID of logged in user (empty if logged out)

    // Helper functions
    void addSampleData();
    void showHeader(string title) const;
    void pauseScreen() const;
    Student* findStudentByID(string id);
    Ride* findRideByID(int id);
    BookingRequest* findRequestByID(int id);
    void bubbleSortRidesByFare(vector<Ride>& list);

public:
    CarpoolSystem();

    // Runs the main menu loop
    void run();

    // Menu handlers
    void showMainMenu() const;
    void registerStudent();
    void loginStudent();
    void logoutStudent();
    void offerRide();
    void viewAllRides() const;
    void searchRides() const;
    void filterRidesByVehicle();
    void requestRideBooking();         // Passenger creates a pending booking request
    void processDriverQueue();         // Driver processes their FIFO pending request queue
    void viewMyBookings() const;       // Passenger views their booking requests
    void manageCampusRouteNetwork();   // Campus Route Network submenu (Dijkstra, BFS, Map)
    void showSystemStats() const;
};

#endif
