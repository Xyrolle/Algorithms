#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

class Edge {
public:
	double cost;
	int from, to;
	Edge(int from, int to, double cost)
		: from(from), to(to), cost(cost) {}
		Edge() : from(0), to(0), cost(0) {}
};

vector<double> BellmanFord(const vector<Edge>& edges, int V, int start) {
	vector<double> dist(V, numeric_limits<double>::infinity());
	dist[start] = 0;

	// For each vertex, apply relaxation for all edges
	int cost = 0;
	bool relaxed = true;
	for (int v = 0; v < V - 1 && relaxed; v++) {
		relaxed = false;
		for (auto edge : edges) {
			cost = dist[edge.from] + edge.cost;
			if (cost < dist[edge.to]) 
				dist[edge.to] = cost;
				relaxed = true;
		}
	}

	// Run algorithm a second time to detect which nodes are part of a negative cycle. A negative cycle has occured if we can find a better path beyond the optimal solution.
	relaxed = true;
	for (int v = 0; v < V - 1 && relaxed; v++) {
		relaxed = false;
		for (auto edge : edges) {
			if (dist[edge.from] + edge.cost < dist[edge.to]) 
				dist[edge.to] = -numeric_limits<double>::infinity();
				relaxed = true;
		} 
	}

	return dist;
}

int main() {

	int E = 10, V = 9, start = 0;
	vector<Edge> edges(E);
	edges[0] = Edge(0, 1, 1); 
	edges[1] = Edge(1, 2, 1);
	edges[2] = Edge(2, 4, 1);
	edges[3] = Edge(4, 3, -3);
	edges[4] = Edge(3, 2, 1);
	edges[5] = Edge(1, 5, 4);
	edges[6] = Edge(1, 6, 4);
	edges[7] = Edge(5, 6, 5);
	edges[8] = Edge(6, 7, 4);
	edges[9] = Edge(5, 7, 3);

	vector<double> d = BellmanFord(edges, V, start);

	for (int i = 0; i < V; i++) {
		cout << "The cost to get from node " << start << " to " << i << " is " << d[i] << endl;
	}

	return 0;
}