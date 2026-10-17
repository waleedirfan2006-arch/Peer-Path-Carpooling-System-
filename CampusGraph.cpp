#include "CampusGraph.h"

CampusGraph::CampusGraph() {
    initializeSampleNetwork();
}

// Add a named vertex to the graph
void CampusGraph::addLocation(const string& name) {
    locations.push_back(name);
    // Initialize empty adjacency list entry
    if (adjacencyList.find(name) == adjacencyList.end()) {
        adjacencyList[name] = vector<Edge>();
    }
}

// Add an edge between two locations with estimated distance in kilometers
void CampusGraph::addRoad(const string& from, const string& to, double distanceKm, bool bidirectional) {
    adjacencyList[from].push_back(Edge(to, distanceKm));
    if (bidirectional) {
        adjacencyList[to].push_back(Edge(from, distanceKm));
    }
}

// Initialize sample Karachi transit network around NED University
// Sample distances are illustrative estimates, not verified road-navigation data.
void CampusGraph::initializeSampleNetwork() {
    locations.clear();
    adjacencyList.clear();

    // 1. Add Vertices (Locations)
    addLocation("NED Main Campus");                       // Index 0
    addLocation("Safari Park");                            // Index 1
    addLocation("Johar Chowrangi");                       // Index 2
    addLocation("NIPA Chowrangi");                        // Index 3
    addLocation("Gulshan Chowrangi");                     // Index 4
    addLocation("Safoora Chowrangi");                     // Index 5
    addLocation("Millennium Mall");                       // Index 6
    addLocation("Malir Cantt Checkpost");                 // Index 7
    addLocation("Saddar Regal Chowk");                    // Index 8
    addLocation("Manora Island Outpost (Isolated Node)"); // Index 9: Intentionally disconnected for testing

    // 2. Add Weighted Undirected Edges (Estimated distances in kilometers)
    // Roads around NED Main Campus / University Road
    addRoad("NED Main Campus", "Safari Park", 2.5);
    addRoad("NED Main Campus", "NIPA Chowrangi", 3.2);
    addRoad("NED Main Campus", "Safoora Chowrangi", 4.0);

    // Roads connecting Johar & Safari Park
    addRoad("Safari Park", "Johar Chowrangi", 2.0);
    addRoad("Safari Park", "NIPA Chowrangi", 2.2);

    // Roads connecting Johar & Safoora & Millennium
    addRoad("Johar Chowrangi", "Millennium Mall", 3.5);
    addRoad("Johar Chowrangi", "Safoora Chowrangi", 4.5);

    // Roads connecting NIPA, Gulshan & Millennium
    addRoad("NIPA Chowrangi", "Gulshan Chowrangi", 2.8);
    addRoad("NIPA Chowrangi", "Millennium Mall", 3.8);

    // Roads connecting to outer hubs (Malir & Saddar)
    addRoad("Millennium Mall", "Malir Cantt Checkpost", 6.0);
    addRoad("Safoora Chowrangi", "Malir Cantt Checkpost", 5.0);
    addRoad("Gulshan Chowrangi", "Saddar Regal Chowk", 11.0);
    addRoad("Millennium Mall", "Saddar Regal Chowk", 10.5);

    // Note: "Manora Island Outpost (Isolated Node)" has no edges added to it,
    // making it a disconnected component to test unreachable queries.
}

int CampusGraph::getLocationCount() const {
    return locations.size();
}

string CampusGraph::getLocationByIndex(int index) const {
    if (isValidIndex(index)) {
        return locations[index];
    }
    return "";
}

bool CampusGraph::isValidIndex(int index) const {
    return (index >= 0 && index < static_cast<int>(locations.size()));
}

// Print numbered location selection menu
void CampusGraph::printLocationMenu() const {
    cout << "\nAvailable Campus Transit Locations:\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < locations.size(); i++) {
        cout << "  [" << i << "] " << locations[i];
        if (i == 9) {
            cout << " (Disconnected Node for Testing)";
        }
        cout << "\n";
    }
    cout << "------------------------------------------------------------\n";
}

// Dijkstra's Shortest Path Algorithm
// Uses a Min-Heap priority queue to find the path with the minimum total distance in km.
void CampusGraph::findShortestPathDijkstra(const string& start, const string& destination) const {
    cout << "\n============================================================\n";
    cout << "       DIJKSTRA'S SHORTEST PATH COMPUTATION\n";
    cout << "============================================================\n";
    cout << "  Origin      : " << start << "\n";
    cout << "  Destination : " << destination << "\n";
    cout << "  Note: Distances are illustrative estimates for project demonstration.\n";
    cout << "------------------------------------------------------------\n";

    // Handle identical start and destination
    if (start == destination) {
        cout << "  [i] Origin and Destination are identical.\n";
        cout << "  Route          : " << start << "\n";
        cout << "  Total Distance : 0.0 km\n";
        return;
    }

    // Min-Heap priority queue: stores pairs of (current_distance, vertex_name)
    // greater<...> ensures the element with the smallest distance is always at top()
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> minHeap;

    // Distances map: stores minimum known distance from start to each node
    unordered_map<string, double> distances;

    // Parent map: stores predecessor of each node to reconstruct the shortest path
    unordered_map<string, string> parent;

    // Initialize all distances to infinity
    const double INF = numeric_limits<double>::infinity();
    for (const auto& loc : locations) {
        distances[loc] = INF;
    }

    // Distance to start node is 0
    distances[start] = 0.0;
    minHeap.push({0.0, start});

    while (!minHeap.empty()) {
        auto topPair = minHeap.top();
        double currentDist = topPair.first;
        string u = topPair.second;
        minHeap.pop();

        // If distance in heap is outdated, skip it
        if (currentDist > distances[u]) {
            continue;
        }

        // Optimization: if we reached destination, we can stop
        if (u == destination) {
            break;
        }

        // Relax edges connected to vertex u
        auto it = adjacencyList.find(u);
        if (it != adjacencyList.end()) {
            for (const auto& edge : it->second) {
                string v = edge.destination;
                double weight = edge.distanceKm;

                // Relaxation condition: if path through u to v is shorter
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u; // Record predecessor for route reconstruction
                    minHeap.push({distances[v], v});
                }
            }
        }
    }

    // Check if destination was reached
    if (distances[destination] == INF) {
        cout << "  [-] No route available between '" << start << "' and '" << destination << "'.\n";
        cout << "      (The destination is disconnected or isolated in the transit network)\n";
        return;
    }

    // Reconstruct the shortest path from destination back to start using parent map
    vector<string> path;
    string current = destination;
    while (current != start) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    // Display the computed shortest route
    cout << "  [+] Shortest Path Found!\n\n";
    cout << "  Complete Ordered Route:\n  ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " --> ";
        }
    }
    cout << "\n\n";

    // Display segment-by-segment distance breakdown
    cout << "  Turn-by-Turn Segment Distances:\n";
    for (int i = 0; i < path.size() - 1; i++) {
        string from = path[i];
        string to = path[i + 1];
        double segDist = 0.0;

        for (const auto& edge : adjacencyList.at(from)) {
            if (edge.destination == to) {
                segDist = edge.distanceKm;
                break;
            }
        }
        cout << "    * " << from << " to " << to << " : " << fixed << setprecision(1) << segDist << " km\n";
    }

    cout << "  --------------------------------------------------\n";
    cout << "  Total Commute Distance : " << fixed << setprecision(1) << distances[destination] << " km\n";
}

// Breadth-First Search (BFS) for connectivity / reachability check
// Traverses the graph level by level to check if ANY path exists between two locations.
void CampusGraph::checkReachabilityBFS(const string& start, const string& destination) const {
    cout << "\n============================================================\n";
    cout << "       BREADTH-FIRST SEARCH (BFS) CONNECTIVITY CHECK\n";
    cout << "============================================================\n";
    cout << "  Origin      : " << start << "\n";
    cout << "  Destination : " << destination << "\n";
    cout << "  Note: BFS checks reachability; Dijkstra determines minimum distance.\n";
    cout << "------------------------------------------------------------\n";

    // Handle identical start and destination
    if (start == destination) {
        cout << "  [+] Origin and Destination are identical (Directly Connected).\n";
        return;
    }

    // BFS Queue for level-by-level exploration
    queue<string> bfsQueue;

    // Visited set to prevent revisiting nodes and avoid infinite cycles
    unordered_set<string> visited;

    // Start BFS from origin
    bfsQueue.push(start);
    visited.insert(start);

    bool isConnected = false;
    vector<string> explorationOrder;

    while (!bfsQueue.empty()) {
        string curr = bfsQueue.front();
        bfsQueue.pop();
        explorationOrder.push_back(curr);

        if (curr == destination) {
            isConnected = true;
            break;
        }

        // Explore all adjacent unvisited neighbors
        auto it = adjacencyList.find(curr);
        if (it != adjacencyList.end()) {
            for (const auto& edge : it->second) {
                if (visited.find(edge.destination) == visited.end()) {
                    visited.insert(edge.destination);
                    bfsQueue.push(edge.destination);
                }
            }
        }
    }

    if (isConnected) {
        cout << "  [+] REACHABLE: A valid path exists connecting:\n";
        cout << "      '" << start << "' and '" << destination << "'!\n\n";
        cout << "  BFS Traversal Order (" << explorationOrder.size() << " nodes explored):\n  ";
        for (int i = 0; i < explorationOrder.size(); i++) {
            cout << explorationOrder[i];
            if (i < explorationOrder.size() - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";
    } else {
        cout << "  [-] UNREACHABLE: No path exists between '" << start 
             << "' and '" << destination << "'.\n";
        cout << "      (One of these locations is in an isolated or disconnected network)\n";
    }
}

// Display the complete network adjacency list
void CampusGraph::displayNetwork() const {
    cout << "\n============================================================\n";
    cout << "       CAMPUS TRANSIT ROAD NETWORK (ADJACENCY LIST)\n";
    cout << "============================================================\n";
    cout << "  Total Locations (Vertices) : " << locations.size() << "\n";
    cout << "  Note: Distances are illustrative estimates in kilometers.\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < locations.size(); i++) {
        string loc = locations[i];
        cout << "  [" << i << "] " << loc << "\n";

        auto it = adjacencyList.find(loc);
        if (it != adjacencyList.end() && !it->second.empty()) {
            for (const auto& edge : it->second) {
                cout << "      |-- (" << fixed << setprecision(1) << edge.distanceKm 
                     << " km) --> " << edge.destination << "\n";
            }
        } else {
            cout << "      |-- [No road connections - Disconnected Node]\n";
        }
        cout << "\n";
    }
}
