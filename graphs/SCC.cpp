#include<iostream> 
#include <list> 
#include <stack> 
#include <vector>
#define UNVISITED -1 

using namespace std; 
  
class Graph {
	int V;
	list<int> *adj; // Pointer to an array containing adjacency lists

	void SCCUtilDFS(int at, vector<int>& ids, vector<int>& low, stack<int>& st, vector<bool>& onStack);
public: 
	Graph(int V);
	void addEdge(int v, int w);
	void SCC();
}; 
  
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
} 
  
void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
} 
  
void Graph::SCCUtilDFS(int at, vector<int>& ids, vector<int>& low, stack<int>& st, vector<bool>& onStack) {
	static int id = 0;

	// Initialize id and low link value 
	st.push(at);
	ids[at] = low[at] = ++id; 
	onStack[at] = true; 

	// Go through all neighbours & low low-link on callback 
	list<int>::iterator i; 
	for (i = adj[at].begin(); i != adj[at].end(); ++i) {
		int to = *i;  // to is current adjacent of 'at' 

		// If to is not visited yet, then recur for it 
		if (ids[to] == UNVISITED) {
            SCCUtilDFS(to, ids, low, st, onStack);

            // Check if the subtree rooted with 'to' has a
            // connection to one of the ancestors of 'at'
            low[at] = min(low[at], low[to]);
		} 

		else if (onStack[to]) 
			low[at] = min(low[at], low[to]);
	} 

	// After having visited all the neighbours of 'at
	// if we're at the start of a SCC 
	//		empty the seen stack until we're back to the start of SCC
	int node = 0;
	if (low[at] == ids[at]) {
        while (st.top() != at) {
			node = (int) st.top();
			cout << node << " ";
			onStack[node] = false;
			st.pop();
		} 
		node = (int) st.top();
		cout << node << "\n";
		onStack[node] = false;
		st.pop();
	} 
} 
  
void Graph::SCC() {
	// Initialize ids, low-link values and onStack arrays 
	vector<int> ids(V, UNVISITED);
	vector<int> low(V);
	vector<bool> onStack(V);
	stack<int> st;
	
	// find strongly connected components in DFS tree with vertex 'i' 
	for (int i = 0; i < V; i++) 
		if (ids[i] == UNVISITED)
			SCCUtilDFS(i, ids, low, st, onStack);
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

	cout << "\nSCCs in a graph \n";
	g.SCC();

	return 0;	
}
