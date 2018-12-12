#include "Graph.h"

Graph::Graph() {
   nameSize = 0;
   names = nullptr;
   graphSize = 0;
   graph = nullptr; 
}
   
Graph::~Graph() {
   delete[] names;
   for (int i = 0; i < graphSize; ++i) {
      delete[] graph[i];
   }
   delete[] graph;
}

void Graph::AddEdge(string source, string target, int weight) { 
   int sourceIndex = GetIndex(source);
   int targetIndex = GetIndex(target);
   graph[sourceIndex][targetIndex] = weight;  
}

void Graph::AddVertex(string label) {
   AddName(label); 
}

bool Graph::IsEdge(int sourceIndex, int targetIndex) {
   return graph[sourceIndex][targetIndex] != numeric_limits<int>::max();
}

int Graph::GetWeight(int sourceIndex, int targetIndex) {
   return graph[sourceIndex][targetIndex];
}

void Graph::BreadthFirstSearch(string startingVertex) {
	set<int> v;
	queue<int> q;
	int start = GetIndex(startingVertex);
	v.insert(start);
	q.push(start);
	cout << "starting BFS with vertex " << startingVertex << endl;
	while (q.empty() == false) {
		int front = q.front();
		q.pop();
		cout << "\tvisited " << names[front] << endl;
		
		for (int i = 0; i < graphSize; ++i) {
			if (IsEdge(front, i) && v.count(i) == 0) {
				v.insert(i);
				q.push(i);
			}
		}
	}
	cout << endl;
}

void Graph::DijkstraShortestPath(string startingVertex) {
   cout << "Shortest Distance starting from vertex " << startingVertex << endl;
   set<int> Q;
   int *dist = new int[graphSize];
   int *prev = new int[graphSize];
   for (int v = 0; v < graphSize; ++v) {
	   dist[v] = numeric_limits<int>::max();
	   prev[v] = -1;
	   Q.insert(v);
   }
   int source = GetIndex(startingVertex);
   dist[source] = 0;
   while (Q.empty() == false) {
	   int u = -1;
	   for (int v : Q) {
		   if (u == -1 || dist[v] < dist[u]) {
			   u = v;
		   }
	   }
	   Q.erase(u);
	   for (int v = 0; v < graphSize; ++v) {
		   if (IsEdge(u, v) && dist[u] < numeric_limits<int>::max()) {
			   int alt = dist[u] + GetWeight(u, v);
			   if (alt < dist[v]) {
				   dist[v] = alt;
				   prev[v] = u;
			   }
		   }
	   }
   }
   for (int i = 0; i < graphSize; ++i) {
	   if (i == source) {
		   cout << "\tto: " << names[i] << "\t0\tPath: " << names[i] << endl;
	   }
	   else if (prev[i] != -1) {
		   cout << "\tto: " << names[i] << "\t" << dist[i] << "\tPath: ";
		   int v = i;
		   while (v != source) {
			   cout << names[v] << ", ";
			   v = prev[v];
		   }
		   cout << names[v] << endl;
	   }
	   else {
		   cout << "\tto: " << names[i] << "\tno path" << endl;
	   }
   }
   delete[] dist;
   delete[] prev;
   cout << endl;
}

void Graph::PrintGraph() {
	cout << "numVerticies: " << graphSize << endl;
	cout << "\t";
	for (int i = 0; i < nameSize; ++i) {
		cout << names[i] << "\t";
	}
	cout << endl;
	assert(nameSize == graphSize);
	for (int i = 0; i < graphSize; ++i) {
		cout << names[i] << "\t";
		for (int j = 0; j < graphSize; ++j) {
			if (graph[i][j] != numeric_limits<int>::max()) {
			cout << graph[i][j] << "\t";
			}
			else {
			cout << "\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int Graph::GetIndex(string name) {
   for (int i = 0; i < nameSize; ++i) {
      if (names[i] == name) {
         return i;
      }
   }
   return -1; 
}

void Graph::AddName(string name) {
   assert(GetIndex(name) == -1);

   string *oldNames = names;
   names = new string[++nameSize];
   for (int i = 0; i < nameSize - 1; ++i) {
      names[i] = oldNames[i];
   }
   names[nameSize - 1] = name;
   delete[] oldNames;

   int **oldGraph = graph;
   graph = new int*[++graphSize];
   for (int i = 0; i < graphSize; ++i) {
      graph[i] = new int[graphSize];
      for (int j = 0; j < graphSize; ++j) {
         graph[i][j] = numeric_limits<int>::max();
      }
   }
   for (int i = 0; i < graphSize - 1; ++i) {
      for (int j = 0; j < graphSize - 1; ++j) {
         graph[i][j] = oldGraph[i][j];
      }
   }
   for (int i = 0; i < graphSize - 1; ++i) {
         delete[] oldGraph[i];
   }
   delete[] oldGraph;  
}

