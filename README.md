# Peer-Path-Carpooling-System-

PeerPath is a decentralized campus ride-sharing and carpooling system tailored for NED University students and faculty. Built to optimize daily commutes, the platform intelligently matches users traveling on similar routes, fostering a trusted peer-to-peer transit network while promoting eco-friendly campus travel.

---

## Table of Contents
1. [Project Overview](#project-overview)
2. [Data Structures & Algorithms (DSA) Implementation](#data-structures--algorithms-dsa-implementation)
3. [Campus Route Network Feature](#campus-route-network-feature)
   - [Graph Representation & Edge Weights](#graph-representation--edge-weights)
   - [Breadth-First Search (BFS) Connectivity](#breadth-first-search-bfs-connectivity)
   - [Dijkstra's Algorithm (Shortest Weighted Path)](#dijkstras-algorithm-shortest-weighted-path)
   - [Sample Karachi & Campus Locations](#sample-karachi--campus-locations)
4. [System Features & Menu Options](#system-features--menu-options)
5. [Compilation and Execution Guide](#compilation-and-execution-guide)
6. [Example CLI Usage & Output](#example-cli-usage--output)
7. [System Limitations & Future Enhancements](#system-limitations--future-enhancements)

---

## Project Overview

PeerPath provides a CLI-based carpooling management system designed in standard C++17. It manages student/faculty accounts, active ride postings for cars and bikes, seat availability, ride fare sorting, booking requests managed via FIFO queues, and a campus transit route network.

---

## Data Structures & Algorithms (DSA) Implementation

PeerPath demonstrates core computer science data structures and algorithms:

- **Custom Structs & Object-Oriented Design**: Encapsulation of `Student`, `Ride`, `BookingRequest`, and `Edge` with modular class architectures.
- **Dynamic Arrays (`std::vector`)**: Used for storing registered accounts, listed rides, request archives, and location indexing.
- **Queue Data Structure (`std::queue`)**: Manages pending passenger ride booking requests in strict FIFO (First-In, First-Out) order. Also used in Breadth-First Search (BFS) for level-order graph exploration.
- **Min-Heap Priority Queue (`std::priority_queue` with `std::greater`)**: Powers Dijkstra's shortest-path algorithm to efficiently extract the next unvisited vertex with the minimum cumulative distance.
- **Hash Maps (`std::unordered_map`) & Hash Sets (`std::unordered_set`)**: Stores the graph's Adjacency List (`unordered_map<string, vector<Edge>>`), tracks visited states in BFS, and tracks shortest distance mappings and predecessor parent pointers in Dijkstra.
- **Manual Bubble Sort**: Sorts vehicle-filtered rides by fare in ascending order using nested loops without built-in sorting libraries.
- **Graph Theory**: Models road networks connecting NED University with major Karachi commuter transit hubs as a weighted, undirected graph.

---

## Campus Route Network Feature

The **Campus Route Network** (Main Menu Option 10) allows students and drivers to explore campus transit routes, inspect connectivity, and compute optimal shortest-distance commute paths.

### Graph Representation & Edge Weights
- **Vertices (Nodes)**: Represent physical transit landmarks, gates, chowrangis, and commercial hubs around NED University and Karachi (e.g., NED Main Campus, Safari Park, NIPA Chowrangi, Safoora Chowrangi).
- **Edges (Roads)**: Undirected connections between two locations traversable in both directions.
- **Edge Weights (Distance in Kilometers)**: Each edge weight represents the estimated road distance in kilometers (`km`).
  > **Note**: All sample edge weights are illustrative estimates for project demonstration and algorithm testing; they are not live GPS or verified navigation data.
- **Adjacency List Structure**:
  ```cpp
  struct Edge {
      string destination;
      double distanceKm; // Estimated distance in km
  };

  unordered_map<string, vector<Edge>> adjacencyList;
  ```

### Breadth-First Search (BFS) Connectivity
- **Purpose**: Checks whether a valid road path exists connecting two specified locations.
- **How It Works**:
  1. Starts at the origin vertex and pushes it into a FIFO `std::queue<string>`.
  2. Marks the origin as visited in a `std::unordered_set<string>`.
  3. Dequeues the front vertex level-by-level, exploring all adjacent unvisited neighbors.
  4. If the destination vertex is encountered, reachability is confirmed.
  5. If the queue empties without reaching the destination, the locations are disconnected.
- **Key Distinction**: BFS determines **reachability / connectivity**; it does not guarantee the minimum weighted distance path on weighted graphs.

### Dijkstra's Algorithm (Shortest Weighted Path)
- **Purpose**: Finds the path with the minimum total cumulative distance in kilometers between any two locations.
- **How It Works**:
  1. Maintains a `distances` map initialized to infinity (`INF`) for all vertices, with the starting location set to `0.0`.
  2. Uses a **Min-Heap Priority Queue** (`priority_queue<pair<double, string>, vector<pair<double, string>>, greater<...>>`) storing `(current_distance, vertex_name)`.
  3. In each iteration, extracts the vertex `u` with the smallest known distance.
  4. Relaxes each neighbor `v`: if `distances[u] + weight(u, v) < distances[v]`, updates `distances[v]` and records `parent[v] = u`.
  5. Reconstructs the complete ordered path using the `parent` map by backtracking from destination to start.
  6. Displays turn-by-turn segment distances and total commute distance formatted to 1 decimal place.

### Sample Karachi & Campus Locations
The system includes 10 predefined locations around NED University:
1. `[0] NED Main Campus`
2. `[1] Safari Park`
3. `[2] Johar Chowrangi`
4. `[3] NIPA Chowrangi`
5. `[4] Gulshan Chowrangi`
6. `[5] Safoora Chowrangi`
7. `[6] Millennium Mall`
8. `[7] Malir Cantt Checkpost`
9. `[8] Saddar Regal Chowk`
10. `[9] Manora Island Outpost (Isolated Node)` *(Intentionally disconnected to test unreachable scenarios)*

---

## System Features & Menu Options

1. **Register New Student/Faculty** (`1`): Create an account with student ID, name, department, NED cloud email, phone, and role.
2. **Login** (`2`): Authenticate via Student ID.
3. **Offer a Ride** (`3`): Post a ride specifying pickup, destination, time, date, vehicle type (`Car` or `Bike`), seats, and fare.
4. **View All Available Rides** (`4`): Browse all active carpool offers with complete details.
5. **Search Rides by Location** (`5`): Case-insensitive keyword search matching pickup or destination.
6. **Filter Rides by Vehicle & Sort by Fare** (`6`): Filter rides by `Car` or `Bike` and sort by fare using manual Bubble Sort.
7. **Request Ride Booking** (`7`): Submit a seat booking request placed in the driver's FIFO queue.
8. **View My Booking Requests** (`8`): Track status (`Pending`, `Accepted`, `Rejected`) of submitted booking requests.
9. **View & Process Booking Requests** (`9`): Driver dashboard to process pending requests in FIFO order with seat validation.
10. **Campus Route Network (Graph DSA)** (`10`): Interactive Dijkstra shortest route, BFS reachability, and adjacency list viewer.
11. **System Statistics & Summary** (`11`): Display user, ride, and seat counts.
12. **Logout** (`12`): Terminate the current session.
0. **Exit** (`0`): Exit the application cleanly.

---

## Compilation and Execution Guide

### Prerequisites
- Windows OS (or Linux/macOS with standard terminal)
- GCC / MinGW with C++17 support (`g++`)

### Compilation Commands

#### Option A: Using the Windows Batch Script
Double click or run from CMD / PowerShell:
```bat
.\build.bat
```

#### Option B: Direct g++ Command Line
```bash
g++ -std=c++17 main.cpp Student.cpp Ride.cpp CarpoolSystem.cpp CampusGraph.cpp -o peerpath.exe
```

### Running the Application
```bat
.\peerpath.exe
```

---

## Example CLI Usage & Output

### 1. Shortest Route Calculation (Dijkstra)
```text
============================================================
       DIJKSTRA'S SHORTEST PATH COMPUTATION
============================================================
  Origin      : NED Main Campus
  Destination : Millennium Mall
  Note: Distances are illustrative estimates for project demonstration.
------------------------------------------------------------
  [+] Shortest Path Found!

  Complete Ordered Route:
  NED Main Campus --> NIPA Chowrangi --> Millennium Mall

  Turn-by-Turn Segment Distances:
    * NED Main Campus to NIPA Chowrangi : 3.2 km
    * NIPA Chowrangi to Millennium Mall : 3.8 km
  --------------------------------------------------
  Total Commute Distance : 7.0 km
```

### 2. Reachability Check (BFS)
```text
============================================================
       BREADTH-FIRST SEARCH (BFS) CONNECTIVITY CHECK
============================================================
  Origin      : NED Main Campus
  Destination : Saddar Regal Chowk
  Note: BFS checks reachability; Dijkstra determines minimum distance.
------------------------------------------------------------
  [+] REACHABLE: A valid path exists connecting:
      'NED Main Campus' and 'Saddar Regal Chowk'!

  BFS Traversal Order (8 nodes explored):
  NED Main Campus -> Safari Park -> NIPA Chowrangi -> Safoora Chowrangi -> Johar Chowrangi -> Gulshan Chowrangi -> Millennium Mall -> Saddar Regal Chowk
```

### 3. Isolated / Unreachable Node Handling
```text
============================================================
       DIJKSTRA'S SHORTEST PATH COMPUTATION
============================================================
  Origin      : NED Main Campus
  Destination : Manora Island Outpost (Isolated Node)
  Note: Distances are illustrative estimates for project demonstration.
------------------------------------------------------------
  [-] No route available between 'NED Main Campus' and 'Manora Island Outpost (Isolated Node)'.
      (The destination is disconnected or isolated in the transit network)
```

---

## System Limitations & Future Enhancements

1. **In-Memory Storage**: Current session data, user accounts, and booking queues exist in runtime memory; persistent database storage (SQLite / MySQL) or file serialization is planned for future phases.
2. **Estimated Distances**: Road distances are illustrative estimates designed to demonstrate graph algorithms and alternative route selections; live GPS or mapping API integrations (Google Maps / OpenStreetMap) are not incorporated.
3. **Static Traffic Conditions**: Edge weights are static distance values and do not factor in dynamic Karachi traffic congestion, peak commute hours, or road closures.
