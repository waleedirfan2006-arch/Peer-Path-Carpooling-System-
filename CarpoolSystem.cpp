#include "CarpoolSystem.h"

// Helper function to convert a string to lowercase for case-insensitive searching
string toLowercase(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

// Constructor
CarpoolSystem::CarpoolSystem() {
    nextRideID = 101;
    nextRequestID = 1;
    loggedInStudentID = "";
    addSampleData();
}

// Add sample data so the system has records ready to test
void CarpoolSystem::addSampleData() {
    // Add sample students and faculty
    students.push_back(Student("CS-024", "Waleed Irfan", "Computer Science",
                               "cs024@cloud.neduet.edu.pk", "0300-1234567", "Student"));
    students.push_back(Student("SE-088", "Ayesha Khan", "Software Engineering",
                               "se088@cloud.neduet.edu.pk", "0312-9876543", "Student"));
    students.push_back(Student("FAC-102", "Dr. Farooq Hassan", "Computer Science",
                               "farooq@neduet.edu.pk", "0333-5551234", "Faculty"));
    students.push_back(Student("EE-042", "Bilal Ahmed", "Electrical Engineering",
                               "ee042@cloud.neduet.edu.pk", "0345-8889900", "Student"));

    // Add sample carpool rides (Car and Bike)
    rides.push_back(Ride(nextRideID++, "CS-024", "Waleed Irfan",
                         "Johar Chowrangi", "NED Main Campus",
                         "07:30 AM", "2026-10-20", 3, 150.0, "Car"));
    rides.push_back(Ride(nextRideID++, "FAC-102", "Dr. Farooq Hassan",
                         "Gulshan Block 13D", "NED Main Campus",
                         "08:00 AM", "2026-10-20", 1, 80.0, "Bike"));
    rides.push_back(Ride(nextRideID++, "EE-042", "Bilal Ahmed",
                         "Malir Cantt Checkpost", "NED Main Campus",
                         "07:15 AM", "2026-10-20", 4, 200.0, "Car"));
    rides.push_back(Ride(nextRideID++, "SE-088", "Ayesha Khan",
                         "NED Main Campus", "Saddar Regal Chowk",
                         "04:30 PM", "2026-10-20", 1, 120.0, "Bike"));

    // Add sample booking requests in FIFO order (oldest first for driver CS-024)
    allRequests.push_back(BookingRequest(nextRequestID++, 101, "SE-088", "Ayesha Khan",
                                         "CS-024", "Johar Chowrangi", "NED Main Campus", 1));
    allRequests.push_back(BookingRequest(nextRequestID++, 101, "EE-042", "Bilal Ahmed",
                                         "CS-024", "Johar Chowrangi", "NED Main Campus", 1));
}

// Display a section header with current user banner
void CarpoolSystem::showHeader(string title) const {
    cout << "\n============================================================\n";
    cout << "        PEERPATH - NED UNIVERSITY CARPOOLING SYSTEM\n";
    cout << "                 " << title << "\n";
    cout << "============================================================\n";

    if (loggedInStudentID != "") {
        cout << "  Logged in as ID: " << loggedInStudentID << "\n";
        cout << "------------------------------------------------------------\n";
    }
}

// Pause and wait for user to press Enter
void CarpoolSystem::pauseScreen() const {
    cout << "\nPress Enter to return to menu...";
    cin.ignore(10000, '\n');
}

// Linear search to find a student by ID
Student* CarpoolSystem::findStudentByID(string id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == id) {
            return &students[i];
        }
    }
    return nullptr;
}

// Linear search to find a ride by ID
Ride* CarpoolSystem::findRideByID(int id) {
    for (int i = 0; i < rides.size(); i++) {
        if (rides[i].getRideID() == id) {
            return &rides[i];
        }
    }
    return nullptr;
}

// Linear search to find a booking request by ID
BookingRequest* CarpoolSystem::findRequestByID(int id) {
    for (int i = 0; i < allRequests.size(); i++) {
        if (allRequests[i].requestID == id) {
            return &allRequests[i];
        }
    }
    return nullptr;
}

// Print main menu options
void CarpoolSystem::showMainMenu() const {
    showHeader("MAIN MENU");
    cout << "  [1] Register New Student / Faculty\n";
    cout << "  [2] " << (loggedInStudentID == "" ? "Login User" : "Switch User / Login") << "\n";
    cout << "  [3] Offer a New Ride (Driver Mode)\n";
    cout << "  [4] View All Available Rides\n";
    cout << "  [5] Search Rides by Location or Date\n";
    cout << "  [6] Filter Rides by Vehicle & Sort by Fare (Bubble Sort)\n";
    cout << "  [7] Request to Book a Seat (Passenger Mode)\n";
    cout << "  [8] View My Booking Requests (Passenger Mode)\n";
    cout << "  [9] View & Process Booking Requests (Driver Queue - DSA FIFO Queue)\n";
    cout << "  [10] Campus Route Network (DSA Graph, BFS & Dijkstra)\n";
    cout << "  [11] View System Summary & Statistics\n";
    if (loggedInStudentID != "") {
        cout << "  [12] Logout Current User\n";
    }
    cout << "  [0] Exit Application\n";
    cout << "============================================================\n";
    cout << "Enter your choice: ";
}

// Register a new student or faculty member
void CarpoolSystem::registerStudent() {
    showHeader("REGISTRATION");

    int roleChoice = 1;
    cout << "Select Role:\n  [1] Student\n  [2] Faculty Member\nChoice: ";
    if (!(cin >> roleChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        roleChoice = 1;
    } else {
        cin.ignore(10000, '\n');
    }

    string role = (roleChoice == 2) ? "Faculty" : "Student";
    string id, name, department, email, phone;

    cout << "Enter " << (role == "Faculty" ? "Faculty ID" : "Roll Number (e.g., CS-024)") << ": ";
    getline(cin, id);

    // Check if ID is already registered
    if (findStudentByID(id) != nullptr) {
        cout << "\n[!] Error: A user with ID '" << id << "' is already registered.\n";
        pauseScreen();
        return;
    }

    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter NED Email: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phone);

    // Add new student to the vector
    students.push_back(Student(id, name, department, email, phone, role));
    loggedInStudentID = id;

    cout << "\n[+] Registration successful! You are now logged in as " << name << ".\n";
    pauseScreen();
}

// Login with student ID
void CarpoolSystem::loginStudent() {
    showHeader("LOGIN");
    cout << "Enter your NED Roll Number or Faculty ID: ";
    string id;
    getline(cin, id);

    Student* student = findStudentByID(id);
    if (student != nullptr) {
        loggedInStudentID = id;
        cout << "\n[+] Welcome back, " << student->getStudentName()
             << " (" << student->getRole() << ")!\n";
    } else {
        cout << "\n[-] User with ID '" << id << "' not found. Please register first.\n";
    }
    pauseScreen();
}

// Logout current user
void CarpoolSystem::logoutStudent() {
    if (loggedInStudentID != "") {
        Student* student = findStudentByID(loggedInStudentID);
        string name = (student != nullptr) ? student->getStudentName() : loggedInStudentID;
        cout << "\n[+] Logged out " << name << " successfully.\n";
        loggedInStudentID = "";
    }
    pauseScreen();
}

// Offer a new ride
void CarpoolSystem::offerRide() {
    showHeader("OFFER A RIDE (DRIVER MODE)");

    if (loggedInStudentID == "") {
        cout << "[-] Please log in first to offer a ride.\n";
        pauseScreen();
        return;
    }

    Student* driver = findStudentByID(loggedInStudentID);
    string driverName = (driver != nullptr) ? driver->getStudentName() : "Unknown";

    int vehicleChoice = 1;
    cout << "Select Vehicle Type:\n  [1] Car\n  [2] Bike\nChoice: ";
    while (!(cin >> vehicleChoice) || (vehicleChoice != 1 && vehicleChoice != 2)) {
        cout << "Invalid. Please enter 1 for Car or 2 for Bike: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    string vehicleType = (vehicleChoice == 2) ? "Bike" : "Car";

    string pickup, destination, time, date;
    int seats = 1;
    double price = 0.0;

    cout << "Enter Pickup Location (e.g., Johar, Gulshan, Malir): ";
    getline(cin, pickup);
    cout << "Enter Destination (e.g., NED Main Campus): ";
    getline(cin, destination);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Departure Time (e.g., 07:30 AM): ";
    getline(cin, time);

    int maxSeats = (vehicleType == "Bike") ? 1 : 6;
    cout << "Enter Total Passenger Seats (1-" << maxSeats << "): ";
    while (!(cin >> seats) || seats <= 0 || seats > maxSeats) {
        cout << "Invalid. Enter a number between 1 and " << maxSeats << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter Fuel-Share Fare per seat in PKR (e.g., 150): ";
    while (!(cin >> price) || price < 0.0) {
        cout << "Invalid. Enter a valid positive amount: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    rides.push_back(Ride(nextRideID++, loggedInStudentID, driverName,
                         pickup, destination, time, date, seats, price, vehicleType));

    cout << "\n[+] Ride successfully posted with Ride ID #" << (nextRideID - 1) << " (" << vehicleType << ")!\n";
    pauseScreen();
}

// View all rides in the system
void CarpoolSystem::viewAllRides() const {
    showHeader("ALL AVAILABLE RIDES");

    if (rides.size() == 0) {
        cout << "  No rides currently available.\n";
    } else {
        cout << "  Total Rides Listed: " << rides.size() << "\n\n";
        for (int i = 0; i < rides.size(); i++) {
            rides[i].displayRide();
        }
    }
    pauseScreen();
}

// Search rides by keyword in pickup, destination, or date
void CarpoolSystem::searchRides() const {
    showHeader("SEARCH RIDES");

    cout << "Enter location or date to search (e.g., 'Johar', 'Gulshan', 'NED'): ";
    string query;
    getline(cin, query);

    string queryLower = toLowercase(query);
    int matchesFound = 0;

    cout << "\nSearch results for '" << query << "':\n\n";

    for (int i = 0; i < rides.size(); i++) {
        string pickupLower = toLowercase(rides[i].getPickupLocation());
        string destLower = toLowercase(rides[i].getDestination());
        string dateLower = toLowercase(rides[i].getRideDate());

        // Check if query is a substring of pickup, destination, or date
        if (pickupLower.find(queryLower) != string::npos ||
            destLower.find(queryLower) != string::npos ||
            dateLower.find(queryLower) != string::npos) {
            rides[i].displayRide();
            matchesFound++;
        }
    }

    if (matchesFound == 0) {
        cout << "  [-] No rides found matching '" << query << "'.\n";
    } else {
        cout << "  [+] Found " << matchesFound << " matching ride(s).\n";
    }

    pauseScreen();
}

// Sort rides from lowest fare to highest fare using Bubble Sort
void CarpoolSystem::bubbleSortRidesByFare(vector<Ride>& list) {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].getFare() > list[j + 1].getFare()) {
                Ride temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

// Filter rides by vehicle type and display them in ascending fare order
void CarpoolSystem::filterRidesByVehicle() {
    showHeader("FILTER RIDES BY VEHICLE & SORT BY FARE");

    int vehicleChoice = 0;
    cout << "Select Vehicle Type:\n  [1] Car\n  [2] Bike\nChoice: ";
    while (!(cin >> vehicleChoice) || (vehicleChoice != 1 && vehicleChoice != 2)) {
        cout << "Invalid. Please enter 1 for Car or 2 for Bike: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    string vehicleType = (vehicleChoice == 2) ? "Bike" : "Car";
    vector<Ride> matchingRides;
    for (int i = 0; i < rides.size(); i++) {
        if (rides[i].getVehicleType() == vehicleType) {
            matchingRides.push_back(rides[i]);
        }
    }

    if (matchingRides.size() == 0) {
        cout << "  No " << vehicleType << " rides available.\n";
    } else {
        bubbleSortRidesByFare(matchingRides);
        cout << "\n  " << vehicleType << " rides sorted by fare (lowest to highest):\n\n";
        for (int i = 0; i < matchingRides.size(); i++) {
            matchingRides[i].displayRide();
        }
    }
    pauseScreen();
}

// Request to book seat(s) on a ride (Passenger Mode)
void CarpoolSystem::requestRideBooking() {
    showHeader("REQUEST A SEAT (PASSENGER MODE)");

    if (loggedInStudentID == "") {
        cout << "[-] Please log in first to request a seat on a ride.\n";
        pauseScreen();
        return;
    }

    cout << "Enter Ride ID to request (e.g., 101): ";
    int rideID;
    if (!(cin >> rideID)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[-] Invalid input format.\n";
        pauseScreen();
        return;
    }
    cin.ignore(10000, '\n');

    Ride* ride = findRideByID(rideID);
    if (ride == nullptr) {
        cout << "\n[-] Ride ID #" << rideID << " not found.\n";
        pauseScreen();
        return;
    }

    // Validation: Driver cannot request seats on their own ride
    if (ride->getDriverID() == loggedInStudentID) {
        cout << "\n[-] You cannot request seats on your own offered ride!\n";
        pauseScreen();
        return;
    }

    // Validation: Check if ride is active and has seats available
    if (ride->getStatus() != "Active") {
        cout << "\n[-] Sorry, this ride is no longer active!\n";
        pauseScreen();
        return;
    }

    if (ride->getAvailableSeats() <= 0) {
        cout << "\n[-] Sorry, this ride has no empty seats remaining!\n";
        pauseScreen();
        return;
    }

    // Validation: Prevent duplicate pending requests for the same ride
    for (int i = 0; i < allRequests.size(); i++) {
        if (allRequests[i].rideID == rideID &&
            allRequests[i].studentID == loggedInStudentID &&
            allRequests[i].status == "Pending") {
            cout << "\n[-] You already have a pending booking request (#" 
                 << allRequests[i].requestID << ") for this ride!\n";
            cout << "    Please wait for the driver to accept or reject it.\n";
            pauseScreen();
            return;
        }
    }

    // Ask how many seats to request
    int seats = 1;
    cout << "Enter number of seats to request (1 to " << ride->getAvailableSeats() << "): ";
    while (!(cin >> seats) || seats <= 0 || seats > ride->getAvailableSeats()) {
        cout << "Invalid. Enter a number between 1 and " << ride->getAvailableSeats() << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    Student* passenger = findStudentByID(loggedInStudentID);
    string passengerName = (passenger != nullptr) ? passenger->getStudentName() : loggedInStudentID;

    // Create the booking request and store in master record
    allRequests.push_back(BookingRequest(nextRequestID++, rideID, loggedInStudentID, passengerName,
                                         ride->getDriverID(), ride->getPickupLocation(),
                                         ride->getDestination(), seats));

    cout << "\n[+] Booking request #" << (nextRequestID - 1) << " submitted successfully!\n";
    cout << "    Ride #" << ride->getRideID() << " | " << ride->getPickupLocation() 
         << " -> " << ride->getDestination() << "\n";
    cout << "    Driver: " << ride->getDriverName() << " (" << ride->getDriverID() << ")\n";
    cout << "    Requested Seats: " << seats << "\n";
    cout << "    Status: Pending driver approval (Enqueued into driver's FIFO queue)\n";
    pauseScreen();
}

// View all booking requests submitted by the currently logged-in student
void CarpoolSystem::viewMyBookings() const {
    showHeader("MY BOOKING REQUESTS (PASSENGER VIEW)");

    if (loggedInStudentID == "") {
        cout << "[-] Please log in first to view your booking requests.\n";
        pauseScreen();
        return;
    }

    int count = 0;
    cout << "  Booking history for " << loggedInStudentID << ":\n\n";

    for (int i = 0; i < allRequests.size(); i++) {
        if (allRequests[i].studentID == loggedInStudentID) {
            allRequests[i].displayRequest();
            count++;
        }
    }

    if (count == 0) {
        cout << "  You have not submitted any booking requests yet.\n";
    } else {
        cout << "  Total Requests: " << count << "\n";
    }

    pauseScreen();
}

// Process booking requests in FIFO order using C++ STL queue (#include <queue>)
void CarpoolSystem::processDriverQueue() {
    showHeader("DRIVER BOOKING REQUEST QUEUE (DSA FIFO QUEUE)");

    if (loggedInStudentID == "") {
        cout << "[-] Please log in as a driver to view and process booking requests.\n";
        pauseScreen();
        return;
    }

    // 1. Reconstruct the FIFO Queue of pending requests for the logged-in driver.
    // Oldest requests arrived first and will be processed first (FIFO).
    queue<BookingRequest> pendingQueue;

    for (int i = 0; i < allRequests.size(); i++) {
        // Enforce authorization: only requests matching this driver and with status 'Pending'
        if (allRequests[i].driverID == loggedInStudentID && allRequests[i].status == "Pending") {
            // ENQUEUE (push): Insert into the FIFO queue
            pendingQueue.push(allRequests[i]);
        }
    }

    // 2. EMPTY QUEUE CHECK: Handle empty queue gracefully
    if (pendingQueue.empty()) {
        cout << "  [i] You have no pending booking requests in your queue.\n";
        pauseScreen();
        return;
    }

    cout << "  You have " << pendingQueue.size() << " pending request(s) waiting in your queue.\n";
    cout << "  Requests are processed in First-In, First-Out (FIFO) order.\n";

    // 3. Process requests one by one from the front of the queue
    while (!pendingQueue.empty()) {
        // FRONT / PEEK: Inspect the oldest request at the front of the queue
        BookingRequest current = pendingQueue.front();

        Ride* ride = findRideByID(current.rideID);
        int availableSeatsOnRide = (ride != nullptr) ? ride->getAvailableSeats() : 0;

        cout << "\n============================================================\n";
        cout << "  CURRENT REQUEST AT FRONT OF QUEUE (Oldest Pending):\n";
        cout << "============================================================\n";
        cout << "  Request ID     : #" << current.requestID << "\n";
        cout << "  Ride ID        : #" << current.rideID << " (" 
             << current.pickupLocation << " -> " << current.destination << ")\n";
        cout << "  Passenger Name : " << current.studentName << " (ID: " << current.studentID << ")\n";
        cout << "  Seats Requested: " << current.requestedSeats << "\n";
        cout << "  Seats Available: " << availableSeatsOnRide << "\n";
        cout << "------------------------------------------------------------\n";
        cout << "Actions:\n";
        cout << "  [1] Accept Request (Reserve Seats)\n";
        cout << "  [2] Reject Request\n";
        cout << "  [0] Stop & Return to Menu (Leave remaining in queue)\n";
        cout << "Enter decision: ";

        int decision = 0;
        while (!(cin >> decision) || (decision != 0 && decision != 1 && decision != 2)) {
            cout << "Invalid. Enter 1 to Accept, 2 to Reject, or 0 to Stop: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        if (decision == 0) {
            cout << "\n[i] Stopped queue processing. Remaining requests stay pending.\n";
            break;
        }

        // Find the persistent record in allRequests
        BookingRequest* masterReq = findRequestByID(current.requestID);

        if (decision == 1) {
            // ACCEPT: Check available seats to prevent overbooking
            if (ride == nullptr) {
                cout << "\n[-] Error: Associated ride no longer exists.\n";
                // DEQUEUE (pop) invalid request
                pendingQueue.pop();
            } else if (ride->getAvailableSeats() < current.requestedSeats) {
                cout << "\n[-] Cannot Accept: Insufficient seats remaining on this ride!\n";
                cout << "    Requested: " << current.requestedSeats 
                     << " | Available: " << ride->getAvailableSeats() << "\n";
                cout << "    Would you like to reject this request? (1: Yes, 2: Keep in queue): ";
                int rejectChoice = 1;
                cin >> rejectChoice;
                cin.ignore(10000, '\n');
                if (rejectChoice == 1) {
                    if (masterReq != nullptr) masterReq->status = "Rejected";
                    cout << "[-] Request #" << current.requestID << " marked as Rejected.\n";
                    pendingQueue.pop();
                }
            } else {
                // Reserve seats safely without exceeding capacity
                ride->bookSeats(current.requestedSeats);
                if (masterReq != nullptr) {
                    masterReq->status = "Accepted";
                }
                cout << "\n[+] Request #" << current.requestID << " ACCEPTED!\n";
                cout << "    " << current.requestedSeats << " seat(s) reserved for " 
                     << current.studentName << ".\n";
                cout << "    Seats remaining on Ride #" << ride->getRideID() 
                     << ": " << ride->getAvailableSeats() << "\n";

                // DEQUEUE (pop): Remove the processed request from the queue
                pendingQueue.pop();
            }
        } else if (decision == 2) {
            // REJECT: Do not reserve seats, update status to Rejected
            if (masterReq != nullptr) {
                masterReq->status = "Rejected";
            }
            cout << "\n[-] Request #" << current.requestID << " REJECTED. No seats were reserved.\n";

            // DEQUEUE (pop): Remove the processed request from the queue
            pendingQueue.pop();
        }

        // Check if more requests remain
        if (!pendingQueue.empty() && decision != 0) {
            cout << "\n--> Moving to next pending request (" 
                 << pendingQueue.size() << " remaining in queue)...\n";
        }
    }

    if (pendingQueue.empty()) {
        cout << "\n[+] All pending requests in your queue have been processed!\n";
    }

    pauseScreen();
}

// Campus Route Network Submenu (DSA Graph, BFS, and Dijkstra)
void CarpoolSystem::manageCampusRouteNetwork() {
    int choice = -1;
    while (choice != 0) {
        showHeader("CAMPUS ROUTE NETWORK (GRAPH DSA)");
        cout << "  [1] Find Shortest Route (Dijkstra's Algorithm)\n";
        cout << "  [2] Check Route Reachability / Connectivity (BFS Algorithm)\n";
        cout << "  [3] View All Campus Transit Locations & Roads (Adjacency List)\n";
        cout << "  [0] Return to Main Menu\n";
        cout << "============================================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[-] Invalid input. Please enter a number.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            showHeader("FIND SHORTEST ROUTE (DIJKSTRA'S ALGORITHM)");
            campusGraph.printLocationMenu();

            int startIdx = -1, destIdx = -1;
            cout << "\nEnter starting location number [0-" << campusGraph.getLocationCount() - 1 << "]: ";
            if (!(cin >> startIdx) || !campusGraph.isValidIndex(startIdx)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[-] Invalid starting location selection.\n";
                pauseScreen();
                continue;
            }

            cout << "Enter destination location number [0-" << campusGraph.getLocationCount() - 1 << "]: ";
            if (!(cin >> destIdx) || !campusGraph.isValidIndex(destIdx)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[-] Invalid destination location selection.\n";
                pauseScreen();
                continue;
            }
            cin.ignore(10000, '\n');

            string startLoc = campusGraph.getLocationByIndex(startIdx);
            string destLoc = campusGraph.getLocationByIndex(destIdx);

            campusGraph.findShortestPathDijkstra(startLoc, destLoc);
            pauseScreen();

        } else if (choice == 2) {
            showHeader("CHECK ROUTE REACHABILITY (BFS ALGORITHM)");
            campusGraph.printLocationMenu();

            int startIdx = -1, destIdx = -1;
            cout << "\nEnter starting location number [0-" << campusGraph.getLocationCount() - 1 << "]: ";
            if (!(cin >> startIdx) || !campusGraph.isValidIndex(startIdx)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[-] Invalid starting location selection.\n";
                pauseScreen();
                continue;
            }

            cout << "Enter destination location number [0-" << campusGraph.getLocationCount() - 1 << "]: ";
            if (!(cin >> destIdx) || !campusGraph.isValidIndex(destIdx)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[-] Invalid destination location selection.\n";
                pauseScreen();
                continue;
            }
            cin.ignore(10000, '\n');

            string startLoc = campusGraph.getLocationByIndex(startIdx);
            string destLoc = campusGraph.getLocationByIndex(destIdx);

            campusGraph.checkReachabilityBFS(startLoc, destLoc);
            pauseScreen();

        } else if (choice == 3) {
            campusGraph.displayNetwork();
            pauseScreen();

        } else if (choice == 0) {
            cout << "\nReturning to Main Menu...\n";
            break;
        } else {
            cout << "\n[-] Invalid option. Please try again.\n";
            pauseScreen();
        }
    }
}

// Display system statistics
void CarpoolSystem::showSystemStats() const {
    showHeader("SYSTEM STATISTICS & SUMMARY");
    cout << "  Total Registered Users : " << students.size() << "\n";

    int studentCount = 0;
    int facultyCount = 0;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getRole() == "Faculty") {
            facultyCount++;
        } else {
            studentCount++;
        }
    }
    cout << "    - Students : " << studentCount << "\n";
    cout << "    - Faculty  : " << facultyCount << "\n\n";

    cout << "  Total Rides Listed     : " << rides.size() << "\n";
    int activeRides = 0;
    int availableSeats = 0;
    for (int i = 0; i < rides.size(); i++) {
        if (rides[i].getStatus() == "Active") {
            activeRides++;
        }
        availableSeats += rides[i].getAvailableSeats();
    }
    cout << "    - Active Rides        : " << activeRides << "\n";
    cout << "    - Total Empty Seats   : " << availableSeats << "\n";

    pauseScreen();
}

// Main execution loop
void CarpoolSystem::run() {
    int choice = -1;

    while (choice != 0) {
        showMainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[-] Invalid input. Please enter a valid number.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: loginStudent(); break;
            case 3: offerRide(); break;
            case 4: viewAllRides(); break;
            case 5: searchRides(); break;
            case 6: filterRidesByVehicle(); break;
            case 7: requestRideBooking(); break;
            case 8: viewMyBookings(); break;
            case 9: processDriverQueue(); break;
            case 10: manageCampusRouteNetwork(); break;
            case 11: showSystemStats(); break;
            case 12:
                if (loggedInStudentID != "") logoutStudent();
                else cout << "\n[-] Invalid option.\n";
                break;
            case 0:
                showHeader("EXIT");
                cout << "Thank you for using PeerPath Carpooling System.\n";
                cout << "Have a safe commute to NED University!\n\n";
                break;
            default:
                cout << "\n[-] Invalid choice. Please try again.\n";
                pauseScreen();
                break;
        }
    }
}
