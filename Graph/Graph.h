#pragma once
#include <cassert>
#include <limits>
#include <iostream>
#include <set>
#include <string>
#include <queue>
using namespace std;

class Graph {
public:   
   Graph();   
   ~Graph();
   void AddEdge(string source, string target, int weight);
   void AddVertex(string label);
   bool IsEdge(int sourceIndex, int targetIndex);
   int GetWeight(int sourceIndex, int targetIndex);
   void BreadthFirstSearch(string startingVertex);
   void DijkstraShortestPath(string startingVertex);
   void PrintGraph();

private:
   int nameSize;
   string *names;
   int graphSize;
   int **graph;

   int GetIndex(string name);
   void AddName(string name);
};

