//
//
//

#include <iostream>
#include <vector>
#include <list>
#include <assert.h>

using namespace std;

template <class NodeType>
class Graph{
public:
	Graph(){
		directed=true;
	}

	//Create a graph object with the given nodes
	//and initialize the adjacent lists to empty
	Graph (NodeType nodeArray[], int len, bool d);

	//Precondition: from and to nodes are in the vector of nodes
	void AddEdge (const NodeType & from, const NodeType & to);

	//return the adjacent list of node u
	list<int> AdjacentNodes (const NodeType & u);

	int FindNode (const NodeType & u);

	void Display();

		//Explore and visit all vertices of the graph that are
	//reachable from node s in BFS order
	// When finish: Display
	//     * the depth of all reachable vertices (i.e., shortest distance to s)
	//     * the predecessors of all reachable vertices (BFS tree)
	void BFS_Explore (NodeType s);


private:
	bool directed; //true: directed graph, false: undirected graph

	vector<NodeType> nodes;

	//edges[i] stores all nodes that nodes[i] is connected to
	//
	//for undirected graph, we store each edge twice, for example,
	// if node a and b are connected by an edge,
	//   b is in the adjacent list of a, and a is in the adjacent list of b
	vector<list<int>> edges;

};
