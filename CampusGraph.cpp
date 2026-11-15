#include "CampusGraph.h"

CampusGraph::CampusGraph() {
    initializeSampleNetwork();
}

void CampusGraph::addLocation(const string &name) {
    if (adjacencyList.find(name) == adjacencyList.end()) {
        locations.push_back(name);
        adjacencyList[name] = vector<Edge>();
    }
}

void CampusGraph::addRoad(const string &from, const string &to,
                          double distanceKm, bool bidirectional) {
    if (adjacencyList.find(from) == adjacencyList.end() ||
        adjacencyList.find(to) == adjacencyList.end()) {
        return;
    }

    adjacencyList[from].push_back(Edge(to, distanceKm));

    if (bidirectional) {
        adjacencyList[to].push_back(Edge(from, distanceKm));
    }
}

void CampusGraph::initializeSampleNetwork() {
    locations.clear();
    adjacencyList.clear();

    addLocation("NED Main Campus");
    addLocation("Safari Park");
    addLocation("Johar Chowrangi");
    addLocation("NIPA Chowrangi");
    addLocation("Gulshan Chowrangi");
    addLocation("Safoora Chowrangi");
    addLocation("Millennium Mall");
    addLocation("Malir Cantt Checkpost");
    addLocation("Saddar Regal Chowk");
    addLocation("Manora Island Outpost (Isolated Node)");

    addRoad("NED Main Campus", "Safari Park", 2.5);
    addRoad("NED Main Campus", "NIPA Chowrangi", 3.2);
    addRoad("NED Main Campus", "Safoora Chowrangi", 4.0);

    addRoad("Safari Park", "Johar Chowrangi", 2.0);
    addRoad("Safari Park", "NIPA Chowrangi", 2.2);

    addRoad("Johar Chowrangi", "Millennium Mall", 3.5);
    addRoad("Johar Chowrangi", "Safoora Chowrangi", 4.5);

    addRoad("NIPA Chowrangi", "Gulshan Chowrangi", 2.8);
    addRoad("NIPA Chowrangi", "Millennium Mall", 3.8);

    addRoad("Millennium Mall", "Malir Cantt Checkpost", 6.0);
    addRoad("Safoora Chowrangi", "Malir Cantt Checkpost", 5.0);
    addRoad("Gulshan Chowrangi", "Saddar Regal Chowk", 11.0);
    addRoad("Millennium Mall", "Saddar Regal Chowk", 10.5);
}

int CampusGraph::getLocationCount() const {
    return static_cast<int>(locations.size());
}

string CampusGraph::getLocationByIndex(int index) const {
    if (isValidIndex(index)) {
        return locations[index];
    }

    return "";
}

bool CampusGraph::isValidIndex(int index) const {
    return index >= 0 && index < static_cast<int>(locations.size());
}

void CampusGraph::printLocationMenu() const {
    cout << "\nAvailable Campus Transit Locations:\n";
    cout << "------------------------------------------------------------\n";

    for (size_t i = 0; i < locations.size(); i++) {
        cout << "  [" << i << "] " << locations[i];

        if (i == 9) {
            cout << " (Disconnected Node for Testing)";
        }

        cout << "\n";
    }

    cout << "------------------------------------------------------------\n";
}

void CampusGraph::findShortestPathDijkstra(
    const string &start, const string &destination) const {

    cout << "\n============================================================\n";
    cout << "       DIJKSTRA'S SHORTEST PATH COMPUTATION\n";
    cout << "============================================================\n";
    cout << "  Origin      : " << start << "\n";
    cout << "  Destination : " << destination << "\n";
    cout << "------------------------------------------------------------\n";

    if (adjacencyList.find(start) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end()) {
        cout << "Invalid location selected!\n";
        return;
    }

    if (start == destination) {
        cout << "  Origin and Destination are identical.\n";
        cout << "  Route          : " << start << "\n";
        cout << "  Total Distance : 0.0 km\n";
        return;
    }

    priority_queue<pair<double, string>,
                   vector<pair<double, string>>,
                   greater<pair<double, string>>> minHeap;

    unordered_map<string, double> distances;
    unordered_map<string, string> parent;

    const double INF = numeric_limits<double>::infinity();

    for (const auto &loc : locations) {
        distances[loc] = INF;
    }

    distances[start] = 0.0;
    minHeap.push({0.0, start});

    while (!minHeap.empty()) {
        auto topPair = minHeap.top();

        double currentDist = topPair.first;
        string u = topPair.second;

        minHeap.pop();

        if (currentDist > distances[u]) {
            continue;
        }

        if (u == destination) {
            break;
        }

        auto it = adjacencyList.find(u);

        if (it != adjacencyList.end()) {
            for (const auto &edge : it->second) {
                string v = edge.destination;
                double weight = edge.distanceKm;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u;

                    minHeap.push({distances[v], v});
                }
            }
        }
    }

    if (distances[destination] == INF) {
        cout << "No route available between '"
             << start << "' and '" << destination << "'.\n";
        return;
    }

    vector<string> path;
    string current = destination;

    while (current != start) {
        path.push_back(current);

        if (parent.find(current) == parent.end()) {
            cout << "Error reconstructing path.\n";
            return;
        }

        current = parent[current];
    }

    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "\n  Shortest Path Found!\n\n";
    cout << "  Complete Ordered Route:\n  ";

    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];

        if (i + 1 < path.size()) {
            cout << " --> ";
        }
    }

    cout << "\n\n";

    cout << "  Turn-by-Turn Segment Distances:\n";

    for (size_t i = 0; i + 1 < path.size(); i++) {
        string from = path[i];
        string to = path[i + 1];

        double segDist = 0.0;

        for (const auto &edge : adjacencyList.at(from)) {
            if (edge.destination == to) {
                segDist = edge.distanceKm;
                break;
            }
        }

        cout << "    * " << from << " to " << to
             << " : " << fixed << setprecision(1)
             << segDist << " km\n";
    }

    cout << "  --------------------------------------------------\n";
    cout << "  Total Commute Distance : "
         << fixed << setprecision(1)
         << distances[destination] << " km\n";
}

void CampusGraph::checkReachabilityBFS(
    const string &start, const string &destination) const {

    cout << "\n============================================================\n";
    cout << "       BREADTH-FIRST SEARCH (BFS) CONNECTIVITY CHECK\n";
    cout << "============================================================\n";
    cout << "  Origin      : " << start << "\n";
    cout << "  Destination : " << destination << "\n";
    cout << "------------------------------------------------------------\n";

    if (adjacencyList.find(start) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end()) {
        cout << "Invalid location selected!\n";
        return;
    }

    if (start == destination) {
        cout << "Origin and Destination are identical.\n";
        return;
    }

    queue<string> bfsQueue;
    unordered_set<string> visited;

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

        auto it = adjacencyList.find(curr);

        if (it != adjacencyList.end()) {
            for (const auto &edge : it->second) {
                if (visited.find(edge.destination) == visited.end()) {
                    visited.insert(edge.destination);
                    bfsQueue.push(edge.destination);
                }
            }
        }
    }

    if (isConnected) {
        cout << "REACHABLE: A valid path exists connecting:\n";
        cout << start << " and " << destination << "!\n\n";

        cout << "BFS Traversal Order ("
             << explorationOrder.size() << " nodes explored):\n";

        for (size_t i = 0; i < explorationOrder.size(); i++) {
            cout << explorationOrder[i];

            if (i + 1 < explorationOrder.size()) {
                cout << " -> ";
            }
        }

        cout << "\n";
    }
    else {
        cout << "UNREACHABLE: No path exists between '"
             << start << "' and '" << destination << "'.\n";
    }
}

void CampusGraph::displayNetwork() const {
    cout << "\n============================================================\n";
    cout << "       CAMPUS TRANSIT ROAD NETWORK (ADJACENCY LIST)\n";
    cout << "============================================================\n";

    cout << "  Total Locations (Vertices) : "
         << locations.size() << "\n";

    cout << "------------------------------------------------------------\n";

    for (size_t i = 0; i < locations.size(); i++) {
        string loc = locations[i];

        cout << "  [" << i << "] " << loc << "\n";

        auto it = adjacencyList.find(loc);

        if (it != adjacencyList.end() && !it->second.empty()) {
            for (const auto &edge : it->second) {
                cout << "      |-- ("
                     << fixed << setprecision(1)
                     << edge.distanceKm << " km) --> "
                     << edge.destination << "\n";
            }
        }
        else {
            cout << "      |-- [No road connections - Disconnected Node]\n";
        }

        cout << "\n";
    }
}
