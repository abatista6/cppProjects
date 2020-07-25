//
//
//

#include "lab5.h"


//Create a graph object with the given nodes
//and initialize the adjacent lists to empty 
template <class NodeType>
Graph<NodeType>::Graph (NodeType nodeArray[], int len, bool d){
	for (int i=0;i<len;i++)
	{
			nodes.push_back (nodeArray[i]);

			//Initialize adjacent list of nodes[i] to be an empty list 
			list<int> adjacentList;
			edges.push_back (adjacentList);
	}
	directed = d;

}

//Precondition: from and to nodes are in the vector of nodes 
//Find index; go thru all nodes, if it is from node, save to from index
template <class NodeType>
void Graph<NodeType>::AddEdge (const NodeType & from, const NodeType & to){
	int cnt=0;
	int fromIndex, toIndex;

	//Find from and to nodes in the nodes vector 
	for (int i=0;i<nodes.size();i++)
	{
			if (nodes[i]==from)
			{
				fromIndex = i;
				cnt++;
			} 
			if (nodes[i]==to)
			{
				toIndex = i;
				cnt++;
			}

	}

	//check precondition
	assert (cnt==2);

	edges[fromIndex].push_back(toIndex);
	if (!directed) 
		edges[toIndex].push_back (fromIndex);
		
}

//return the adjacent list of node u 
template <class NodeType>
list<int> Graph<NodeType>::AdjacentNodes (const NodeType & u)
{
		for (int i=0;i<nodes.size();i++)
                {
                        if (nodes[i]==u)
				return edges[i]; 
                }
		assert (false);
}

template <class NodeType> 
int Graph<NodeType>::FindNode (const NodeType & u)
{
		for (int i=0;i<nodes.size();i++)
                {
                        if (nodes[i]==u)
				return i;
                }

}

template <class NodeType> 
void Graph<NodeType>::Display(){
		list<int>::iterator it;

		if (directed) 
			cout <<"Directed Graph:\n";
		else
			cout <<"Undirected Graph:\n";

		cout <<"Vertex: {";

		for (int i=0;i<nodes.size();i++)
		{
			cout <<nodes[i]<<" ";
		}
		cout <<"}"<<endl;

		cout <<"Edges:\n{";
		for (int i=0;i<nodes.size();i++)
		{
			for (it=edges[i].begin();it!=edges[i].end();it++)
				if (directed) 
					cout <<"   " <<nodes[i]<<"->"<<nodes[*it]<<","<<endl;
				else
				{
					if (i<=(*it))
						cout <<"   " <<nodes[i]<<"-"<<nodes[*it]<<","<<endl;
				}
		}
		cout <<"}\n";


}

	//Explore and visit all vertices of the graph that are
	//reachable from node s in BFS order
	// When finish: Display
	//     * the depth of all reachable vertices (i.e., shortest distance to s)
	//     * the predecessors of all reachable vertices (BFS tree)
template<NodeType>
void Graph::BFS_Explore (NodeType s);
{


	enum Color=(White, Gray, Black);
	map<NodeType, int> depth; //the depth/hop count of all nodes from s
	map<NodeType, NodeType> pred; //pred[u] is the node that leads us to u
	map<NodeType, Color> color; //color[u] will be White, Gray, or Black
	queue<NodeType> Q;

	//initialize all nodes to white
	for (int i=0; i < nodes.size(); i++)
	{
		color[nodes[i]]=White;
		depth[nodes[i]]=99999;
	}

	//source node init
	color[s]=Gray;
	d[s]=0;

	//insert s into Q
	Q.push(s);

	while(Q.size != 0)
	{
		//get the node in the fron of queue
		NodeType u=Q.front();
		Q.pop();

		//For each node v in Adjacency list of u
		//if it's white, do ... something
		//build a for loop
		list<int> adjNodes = AdjacentNodes(u);

		for(int i=0; i < adjNodes.size(); i++)
		{
			//NodeType v=nodes[adjNodes[i]];
			//how do i access each integer from the list
			//the above is wrong because the index operator
			//isn't supported. find iterator supported
			//by queue class (cplusplus.com)
			for(int j:adjNodes)
			{
				NodeType v = nodes[j];

				if color[v]=White;
				{
					//do something
					color[v]=Gray;
					d[v]=d[u]+1;
					pred[v]=u;
					Q.push(v);
				}
			}
			color[u]=Black;
		}
	}
}


//*** MAIN DRIVER ***

//explicit instantiation of template class
template class Graph<int>;
template class Graph<char>;
//template class Graph<string>;

int main()
{

	//graph.DepthFirstSearch();
	int nodes1[]={10, 20, 30, 40};
	Graph<int> graph1(nodes1,4,false);

	graph1.AddEdge (10,30);
	graph1.AddEdge (10,20);
	graph1.AddEdge (30,40);

	graph1.Display();

	//Interactively build a graph: nodes are string type...
	cout <<"Enter the number of nodes in the graph:";
	int N;
	do{
		cin >> N;
	} while (N<=0);

	string * nodes = new string[N];
        for (int i=0;i<N;i++)
	{
		cout <<"Enter "<<i<<"-th node: ";
		cin >> nodes[i];
	}
	//string nodes[]={"A","B","C","D"};
	Graph<string> graph(nodes,N,true);

	cout <<"Enter the number of edges (directed)";
	int M;
	do {
		cin >> M;
	} while (M<0);

	string fromNode, toNode;
	for (int i=0;i<M;i++)
	{
		cout <<"Enter the "<<i<<"-th edge: from which node:";
		cin >> fromNode;
		cout <<"to which node:";
		cin >> toNode;

		graph.AddEdge (fromNode, toNode);
	}
	/*
	graph.AddEdge ("A","C");
	graph.AddEdge ("A","B");
	graph.AddEdge ("C","D");
	*/

	graph.Display();

}

