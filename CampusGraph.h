#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

// Represents a road connection to an adjacent location
struct Edge {
    string destination;
    double distanceKm; // Estimated distance in kilometers (illustrative)

    Edge(string dest, double dist) : destination(dest), distanceKm(dist) {}
};

// Represents the NED University and Karachi commuter road transit network
class CampusGraph {
private:
    vector<string> locations;                             // Indexed list of location names
    unordered_map<string, vector<Edge>> adjacencyList;     // Adjacency list: location -> list of connected edges

public:
    CampusGraph();

    // Graph construction
    void addLocation(const string& name);
    void addRoad(const string& from, const string& to, double distanceKm, bool bidirectional = true);
    void initializeSampleNetwork();

    // Getters and validation helpers
    int getLocationCount() const;
    string getLocationByIndex(int index) const;
    bool isValidIndex(int index) const;
    void printLocationMenu() const;

    // Core DSA Graph Algorithms
    void findShortestPathDijkstra(const string& start, const string& destination) const;
    void checkReachabilityBFS(const string& start, const string& destination) const;
    void displayNetwork() const;
};

#endif // CAMPUSGRAPH_H
