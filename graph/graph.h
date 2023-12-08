//CS311 graph.h

#pragma once
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <limits>
//#include "heap.h"
using namespace std;

// =======================================================
// Your name: Sarah Turner
// Compiler:  g++ 
// File type: header file  graph.h
//=======================================================

/**
 * @brief Vertex class
 * 
 */
class Vertex {
public:
    int id;          // The index of the vertex. starting from 0
    string cityCode; // 2 letter city code
    string name;     // The name of the vertex. Additional attributes can be added
    int population;  // City population
    int elevation;   // City elevation
    int prev;        // Used to track previous vertex when using DFS or checkCycle
    bool visited;    // Used to track if the vertex has been visited / discovered in DFS or BFS
    double distance; // Used to track distance for shortest path algorithm

    Vertex(int id = 0, string cityCode = "", string name = "", int pop = 0, int elev = 0, int prev = -1, bool visited = false, double dist = 0) {
        this->id = id;
        this->cityCode = cityCode;
        this->name = name;
        this->population = pop;
        this->elevation = elev;
        this->prev = prev;
        this->visited = visited;
        this->distance = dist;
    }

    /**
     * @brief equality comp operator (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator==(const Vertex &other){
        if(this->distance == other.distance) return true;
        return false;
    }

    /**
     * @brief not equal comp operator (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator!=(const Vertex &other){
        if(this->distance == other.distance) return false;
        return true;
    }

    /**
     * @brief less or equal op (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator<=(const Vertex &other){
        if(this->distance <= other.distance) return true;
        return false;
    }

    /**
     * @brief great or equal op (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator>=(const Vertex &other){
        if(this->distance >= other.distance) return true;
        return false;
    }

    /**
     * @brief less op (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator<(const Vertex &other){
        if(this->distance < other.distance) return true;
        return false;
    }

    /**
     * @brief great op (v. dumb, only compares distance)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    bool operator>(const Vertex &other){
        if(this->distance > other.distance) return true;
        return false;
    }

    /**
     * @brief equality operator (smart copies entirely)
     * @param other the heap to be copied
     * @return Heap& a reference to the heap
     */
    Vertex &operator=(const Vertex &other){
        this->id = other.id;
        this->cityCode = other.cityCode;
        this->name = other.name;
        this->population = other.population;
        this->elevation = other.elevation;
        this->prev = other.prev;
        this->visited = other.visited;
        this->distance = other.distance;

        return *this;
    }
};

/**
 * @brief Edge class. It represents an edge from one vertex to another
 * 
 */
struct Edge {
    int from_vertex; // The index of the vertex where the edge starts
    int to_vertex;   // index of the vertex where the edge ends.
    float weight;    // The weight of the edge. Additional attributes can be added

    Edge(int from_vertex = 0, int to_vertex = 0, float weight = 0) {
        this->from_vertex = from_vertex;
        this->to_vertex = to_vertex;
        this->weight = weight;
    }
};

/**
 * @brief Graph class
 *
 */
class Graph
{
public:
    int numVerts;                 // No. of vertices
    vector<Vertex> vertices;      // The list of vertices
    vector<vector<Edge> > adjList; // The adjacency list

    /**
     * @brief Purpose: Default constructor. Create an empty graph
     */ 
    Graph();

    /**
     * @brief Purpose: Constructor to create a graph with n vertices
     */
    Graph(int n);

    /**
     * @brief Purpose: Destructor to get rid of graph
     */
    ~Graph();

    /**
     * @brief Purpose: Add a vertex to the graph
     * @param v: The vertex to be added
     */
    void addVertex(Vertex v);

    /**
     * @brief Purpose: Add a directed edge from v1 to v2 to the graph
     * @param v1: The index of the vertex where the edge starts
     * @param v2: The index of the vertex where the edge ends
     * @param weight: The weight of the edge
     */
    void addDirectedEdge(int v1, int v2, float weight = 1.0f);

    /**
     * @brief Purpose: Add an undirected edge to the graph. An undirected edge is represented by two directed edges.
     * @param v1: The index of the first vertex
     * @param v2: The index of the second vertex
     */
     void addUndirectedEdge(int v1, int v2, float weight = 1.0f);

    /**
     * @brief Purpose: Get the number of outgoing edges from vertex v
     * @param v: The index of the vertex
     * @return The number of outgoing edges from the vertex v
     */
    int outDegree(int v);

    /**
     * @brief Purpose: Depth first search
     * @param v: The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> DepthFirstSearch(int v);

    /**
     * @brief Purpose: Breadth first search
     * @param v: The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> BreadthFirstSearch(int v);

    /**
     * @brief Purpose: Check if the undirected graph contains cycles
     * @return true: the graph has cycles
     * @return false: no cycle exist
     */
    bool checkCycle();

    /**
     * @brief Purpose: Print the graph
     */
    void printGraph();

   /**
    * @brief Purpose: Finds the shortest path between 2 cities using Djikstras Algorithm
    * @param start: Starting vertex
    * @param end: Ending vertex
    * @param &distance: Distance of the shortest path, is returned by reference 
    * @return vector<vertex>: The path taken to get from start to end
    */
    vector<Vertex> dijkstraAlgorithm(Vertex start, Vertex end, double& distance);

};
