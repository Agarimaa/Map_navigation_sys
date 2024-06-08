#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <limits>
using namespace std;

class Place {
public:
    string name;
    unordered_map<Place*, int> neighbours;
    
    Place(string name) : name(name) {}
    
    string getName() const {
        return name;
    }
    
    void addNeighbour(Place* neighbour, int distance) {
        neighbours[neighbour] = distance;
    }
    
    const unordered_map<Place*, int>& getNeighbours() const {
        return neighbours;
    }
};

unordered_map<Place*, int> findShortestPath(Place* start, Place* destination, unordered_map<Place*, Place*>& parent) {
    unordered_map<Place*, int> distances;
    set<Place*> visited;
    
    for (auto neighbor : start->neighbours) {
        distances[neighbor.first] = numeric_limits<int>::max();
    }
    
    distances[start] = 0;
    
    while (visited.find(destination) == visited.end()) {
        Place* closestPlace = nullptr;
        int closestDistance = numeric_limits<int>::max();
        
        for (auto entry : distances) {
            if (visited.find(entry.first) == visited.end() && entry.second < closestDistance) {
                closestPlace = entry.first;
                closestDistance = entry.second;
            }
        }
        
        if (closestPlace == nullptr) {
            break;
        }
        
        visited.insert(closestPlace);
        
        for (auto neighbor : closestPlace->neighbours) {
            int newDistance = distances[closestPlace] + neighbor.second;
            
            if (distances.count(neighbor.first) == 0 || distances[neighbor.first] > newDistance) {
                distances[neighbor.first] = newDistance;
                parent[neighbor.first] = closestPlace;
            }
        }
    }
    
    return distances;
}

vector<Place*> reconstructPath(Place* start, Place* destination, const unordered_map<Place*, Place*>& parent) {
    vector<Place*> path;
    Place* current = destination;
    
    while (current != start) {
        path.insert(path.begin(), current);
        current = parent.at(current);
    }
    
    path.insert(path.begin(), start);
    
    return path;
}

int main() {
    string startName, endName;
    int numNeighbours;
    
    cout << "Enter starting point: ";
    cin >> startName;
    
    cout << "Enter end point: ";
    cin >> endName;
    
    Place startingPoint(startName);
    Place endPoint(endName);
    
    cout << "Enter the number of neighbours for " << startName << ": ";
    cin >> numNeighbours;
    
    for (int i = 0; i < numNeighbours; ++i) {
        string neighbourName;
        int distance;
        
        cout << "Enter neighbour " << i + 1 << " name: ";
        cin >> neighbourName;
        
        cout << "Enter distance from " << startName << " to " << neighbourName << ": ";
        cin >> distance;
        
        Place* neighbour = new Place(neighbourName);
        startingPoint.addNeighbour(neighbour, distance);
    }
    
    unordered_map<Place*, Place*> travelHistory;
    unordered_map<Place*, int> travelDistances = findShortestPath(&startingPoint, &endPoint, travelHistory);
    
    if (travelDistances.count(&endPoint) > 0) {
        cout << "Shortest distance to destination: " << travelDistances[&endPoint] << endl;
        vector<Place*> travelRoute = reconstructPath(&startingPoint, &endPoint, travelHistory);
        cout << "Shortest Path:" << endl;
        
        for (Place* location : travelRoute) {
            cout << location->getName() << " -> ";
        }
        
        cout << "Destination" << endl;
    } else {
        cout << "No path found to destination." << endl;
    }
    
    return 0;
}

