#include <bits/stdc++.h>
using namespace std;

#define INF 999999999

class Graph {
private:
    int no_of_vertices;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) {
        no_of_vertices = vertices;
        adj.resize(no_of_vertices);
    }

    // Add an edge between two vertices with a given weight
    void addEdge(int vertex1, int vertex2, int weight) {
        adj[vertex1].push_back(make_pair(vertex2, weight));
        adj[vertex2].push_back(make_pair(vertex1, weight)); // Since the graph is undirected
    }

    // Remove an edge between two vertices
    void removeEdge(int vertex1, int vertex2) {
        adj[vertex1].erase(
            remove_if(adj[vertex1].begin(), adj[vertex1].end(), [vertex2](pair<int, int> edge) {
                return edge.first == vertex2;
            }), adj[vertex1].end());

        adj[vertex2].erase(
            remove_if(adj[vertex2].begin(), adj[vertex2].end(), [vertex1](pair<int, int> edge) {
                return edge.first == vertex1;
            }), adj[vertex2].end());
    }

    // Add a vertex (Simply increases the number of vertices)
    void addVertex() {
        no_of_vertices++;
        adj.resize(no_of_vertices);
    }

    // Remove a vertex (disconnects all edges from and to the vertex)
    void removeVertex(int vertex) {
        adj[vertex].clear();
        for (int i = 0; i < no_of_vertices; i++) {
            removeEdge(i, vertex);
        }
    }

    // Dijkstra's algorithm to calculate the shortest path
    pair<vector<int>, vector<int>> dijkstra(int source) {
        vector<int> dist(no_of_vertices, INF); // Distance array
        vector<int> parent(no_of_vertices, -1); // Parent array to store the path
        set<pair<int, int>> queue;
        dist[source] = 0;
        queue.insert(make_pair(0, source));

        while (!queue.empty()) {
            pair<int, int> front_p = *(queue.begin());
            queue.erase(queue.begin());
            int cur_dist = front_p.first;
            int node = front_p.second;

            for (auto &edge : adj[node]) {
                int to = edge.first;
                int weight = edge.second;

                if (dist[to] > cur_dist + weight) {
                    if (queue.find(make_pair(dist[to], to)) != queue.end()) {
                        queue.erase(make_pair(dist[to], to));
                    }
                    dist[to] = cur_dist + weight;
                    parent[to] = node;  // Update parent
                    queue.insert(make_pair(dist[to], to));
                }
            }
        }
        return {dist, parent};
    }

    // Function to reconstruct the shortest path
    void printPath(int destination, vector<int> parent) {
        if (parent[destination] == -1) {
            cout << destination + 1 << " "; // Base case (start of the path)
            return;
        }
        printPath(parent[destination], parent);
        cout << destination + 1 << " "; // Print the current node
    }

    void showGraph() {
        cout << "\nGraph Structure (Adjacency List):\n";
        for (int i = 0; i < no_of_vertices; i++) {
            cout << i + 1 << ": ";
            for (auto &edge : adj[i]) {
                cout << "(" << edge.first + 1 << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Enter number of vertices: ";
    int no_of_vertices;
    cin >> no_of_vertices;

    Graph graph(no_of_vertices);

    cout << "Enter number of edges: ";
    int no_of_edges;
    cin >> no_of_edges;

    cout << "Enter edges in the format (vertex1 vertex2 weight):\n";
    for (int i = 0; i < no_of_edges; i++) {
        int vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        vertex1--, vertex2--; // Converting to 0-indexed
        graph.addEdge(vertex1, vertex2, weight);
    }

    int choice;
    while (true) {
        cout << "\n--- Operations Menu ---\n";
        cout << "1. Add Edge\n";
        cout << "2. Remove Edge\n";
        cout << "3. Add Vertex\n";
        cout << "4. Remove Vertex\n";
        cout << "5. Show Graph\n";
        cout << "6. Show Shortest Path (Dijkstra)\n";
        cout << "7. Exit\n";
        cout << "Choose an operation: ";
        cin >> choice;

        if (choice == 1) {
            int vertex1, vertex2, weight;
            cout << "Enter the two vertices and the weight: ";
            cin >> vertex1 >> vertex2 >> weight;
            vertex1--, vertex2--; // 0-indexed
            if(vertex1 > no_of_vertices || vertex2 > no_of_vertices){
                cout<<"Enter the correct vertex"<<endl;
                continue;
            }
            graph.addEdge(vertex1, vertex2, weight);
        }
        else if (choice == 2) {
            int vertex1, vertex2;
            cout << "Enter the two vertices to remove the edge between: ";
            cin >> vertex1 >> vertex2;
            vertex1--, vertex2--; // 0-indexed
            if(vertex1 > no_of_vertices || vertex2 > no_of_vertices){
                cout<<"Enter the correct vertex"<<endl;
                continue;
            }
            graph.removeEdge(vertex1, vertex2);
        }
        else if (choice == 3) {
            graph.addVertex();
            cout << "Vertex added.\n";
        }
        else if (choice == 4) {
            int vertex;
            cout << "Enter the vertex to remove: ";
            cin >> vertex;
            vertex--; // 0-indexed
            if(vertex > no_of_vertices){
                cout<<"Enter the correct vertex"<<endl;
                continue;
            }
            graph.removeVertex(vertex);
            cout << "Vertex removed.\n";
        }
        else if (choice == 5) {
            graph.showGraph();
        }
        else if (choice == 6) {
            int source, destination;
            cout << "Enter the source vertex: ";
            cin >> source;
            cout << "Enter the destination vertex: ";
            cin >> destination;
            source--, destination--; // 0-indexed
            if(source > no_of_vertices || destination > no_of_vertices){
                cout<<"Enter the valid source and destination points"<<endl;
                continue;
            }
            // Get distances and parents
            pair<vector<int>, vector<int>> result = graph.dijkstra(source);
            vector<int> dist = result.first;
            vector<int> parent = result.second;

            if (dist[destination] == INF) {
                cout << "No path exists between " << source + 1 << " and " << destination + 1 << ".\n";
            } else {
                cout << "\nShortest Path from " << source + 1 << " to " << destination + 1 << ":\n";
                graph.printPath(destination, parent);
                cout << "\nShortest Distance: " << dist[destination] << "\n";
            }
        }
        else if (choice == 7) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
