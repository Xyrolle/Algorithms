#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;
  
class Graph {
	int V;
	list<int> *adj; // Pointer to an array containing adjacency lists

	void printAllPathsUtil(int, int , bool [], int [], int &);
  
public:
	Graph(int V);
	void addEdge(int u, int v);
	void printAllPaths(int s, int d);
};
  
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}
  
void Graph::addEdge(int from, int to) {
  adj[from].push_back(to); 
}
  
// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d) {
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
  
    // Create an array to store paths
    int *path = new int[V];
        for (int i = 0; i < V; i++) {
            path[i] = -1;
        }
    int path_index = 0; // Initialize path[] as empty
  
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
  
    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index);
}

void checkHamilton(int path[], int V) {

	int flag = 1;
	
	int aux[V];

	for (int i = 0; i < V; i++) {
		aux[i] = path[i];
	}

	sort(aux, aux + V);

	for (int i = 0; i < V - 1; i++) {
		if (aux[i] == aux[i + 1] || ((aux[i]) == -1) || (aux[i + 1] == -1)) {
			flag = 0;
			break;
		}
	}
	
	if (flag) {
        for (int i = 0; i < V; i++) {
            cout << " " << path[i];
        }
        cout << endl;
    }
}
   
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index) {
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
  
    // If current vertex is same as destination, then check
    // current path[]
    if (u == d) {
      checkHamilton(path, V);
    }
    // If current vertex is not destination
    else {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }
  
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}
  
int main() {
	int v;
	cout << "Number of verticies: ";
	cin >> v;

	Graph g(v);

	int n, val;
	for (int i = 0; i < v; i++) {
		cout << "How many edges: ";
		cin >> n;
		for (int j = 0; j < n; j++) {
			cout << "Add from[" << i << "]: ";
			cin >> val;
			cout << "[" << i << "] -> " << val << endl;
			g.addEdge(i, val);
		}
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (i == j) {
                continue;
			}
            g.printAllPaths(i, j);
		}
	}
		
	return 0;
}
