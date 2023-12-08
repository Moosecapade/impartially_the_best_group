#include "heap.h"
#include <stack>
#include <queue>

// =======================================================
// Your name: Sarah Turner
// Compiler:  g++ 
// File type: implementation file  graph.cpp
//=======================================================

/**
 * @brief Purpose: Default constructor. Create an empty graph
 */ 
Graph::Graph() 
{
    numVerts = 0;
}

/**
 * @brief Purpose: Constructor to create a graph with n vertices
 */
Graph::Graph(int n)
{
    this->numVerts = 0;  // Start with 0 vertices

    for (int i = 0; i < n; ++i)
    {
        Vertex v;                           // Create a new vertex to store in the graph
        v.id = i;                           // Set its index
        v.name = "Vertex " + to_string(i);
        this->vertices.push_back(v);        // Add vertex to the list of vertices
        vector<Edge> list;                  // Used to create an empty list
        this->adjList.push_back(list);      // Add empty list to the adjacency list
        this->numVerts++;
    }
}

/**
 * @brief Purpose: Destructor to get rid of graph
 */
Graph::~Graph()
{
    this->vertices.clear();
    for (int i = 0; i < (int)this->adjList.size(); ++i)
    {
        this->adjList[i].clear();
    }
}

/**
 * @brief Purpose: Add a vertex to the graph
 * @param v: The vertex to be added
 */
void Graph::addVertex(Vertex v)
{
    int index = this->numVerts;            // Used to store id of new vertex
    v.id = index;                          // Set its index
    this->vertices.push_back(v);           // Add vertex to the list of vertices
    vector<Edge> list;                     // Used to create an empty adjacency list
    this->adjList.push_back(list);         // Add empty list to the adjacency list
    this->numVerts++;
}

/**
 * @brief Purpose: Add a directed edge from v1 to v2 to the graph
 * @param v1: The index of the vertex where the edge starts
 * @param v2: The index of the vertex where the edge ends
 * @param weight: The weight of the edge
 */
void Graph::addDirectedEdge(int v1, int v2, float weight)
{
    Edge e(v1, v2, weight);      // Used to create a new edge from v1 to v2
    adjList[v1].push_back(e);    // Store the edge in the adjacency list for v1
}

/**
 * @brief Purpose: Add an undirected edge to the graph. An undirected edge is represented by two directed edges.
 * @param v1: The index of the first vertex
 * @param v2: The index of the second vertex
 */
void Graph::addUndirectedEdge(int v1, int v2, float weight)
{
    addDirectedEdge(v1, v2, weight);
    addDirectedEdge(v2, v1, weight);
}

/**
 * @brief Purpose: Get the number of outgoing edges from vertex v
 * @param v: The index of the vertex
 * @return The number of outgoing edges from the vertex v
 */
int Graph::outDegree(int v)
{
    return this->adjList[v].size();   // Return the number of edges going out from v
}

/**
 * @brief Purpose: Depth first search
 * @param v: The index of the vertex where the search starts
 * @return The list of vertices in the order they are visited
 */
vector<int> Graph::DepthFirstSearch(int v)
{
    vector<int> pathOfTraversal;    // Used to return the path of traversal

    // Case for empty graph:
    if (numVerts == 0)
    {
        return pathOfTraversal;
    }

    // Set prev to -1 and visited to false for all vertices
    for (int i = 0; i < (int)this->vertices.size(); ++i)
    {
        this->vertices[i].prev = -1;
        this->vertices[i].visited = false;
    }

    stack<int> vStack;            // Used to know which vertex to visit next
    vStack.push(v);               // Push starting vertex on stack

    while (!vStack.empty())
    {
        int current = vStack.top();   // Get top vertex index
        vStack.pop();                 // Pop vertex off the stack

        // Visit the node if it is unvisited
        if (this->vertices[current].visited == false)
        {
            this->vertices[current].visited = true;       // Mark the vertex as visited
            pathOfTraversal.push_back(current);           // Update the path of traversal
        }
        // Push current vertex's unvisited neighbors onto stack to be visited next
        for (int i = this->adjList[current].size() - 1; i >= 0; --i)
        {
            int neighbor = this->adjList[current][i].to_vertex;  // Get neighbor vertex

            // Case for unvisited neighbor
            if (this->vertices[neighbor].visited == false)
            {
                vStack.push(neighbor);                     // Push neighbor onto stack
                this->vertices[neighbor].prev = current;   // Set neighbors prev to current vertex
            }
        }
    }

    return pathOfTraversal;  // Return vector of the path beginning at start vertex
}

/**
 * @brief Purpose: Breadth first search
 * @param v: The index of the vertex where the search starts
 * @return The list of vertices in the order they are visited
 */
vector<int> Graph::BreadthFirstSearch(int v)
{
    vector<int> pathOfTraversal;    // Used to track path of BFS traversal

    // Case for empty graph:
    if (this->numVerts == 0)
    {
        return pathOfTraversal;
    }

    // Set discovered to false for all vertices
    for (int i = 0; i < (int)this->vertices.size(); ++i)
    {
        this->vertices[i].visited = false;
    }

    queue<int> frontierQueue;            // Queue of vertices to visit next
    this->vertices[v].visited = true;    // Start vertex is already discovered
    frontierQueue.push(v);               // Enqueue start vertex

    while (!frontierQueue.empty())
    {
        int current = frontierQueue.front();  // Get vertex index from queue
        frontierQueue.pop();                  // Dequeue current vertex
        pathOfTraversal.push_back(current);   // Update path of traversal

        // Enqueue current vertex's undiscovered neighbors to be visited next
        for (int i = 0; i < (int)this->adjList[current].size(); ++i)
        {
            int neighbor = this->adjList[current][i].to_vertex;  // Get neighbor vertex

            // Case where neighbor is undiscovered
            if (this->vertices[neighbor].visited == false)
            {
                frontierQueue.push(neighbor);             // Enqueue neighbor
                this->vertices[neighbor].visited = true;  // Mark as discovered
            }
        }
    }

    return pathOfTraversal;  // Return vector of path beginning at start vertex
}

/**
 * @brief Purpose: Check if the undirected graph contains cycles using DFS
 * @return true: the graph has cycles
 * @return false: no cycle exist
 */
bool Graph::checkCycle()
{
    // Case for empty graph:
    if (numVerts == 0)
    {
        return false;
    }

    // Set visited to false and prev to -1 for all vertices
    for (int i = 0; i < (int)this->vertices.size(); ++i)
    {
        this->vertices[i].visited = false;
        this->vertices[i].prev = -1;
    }

    stack<int> vStack;  // Used to know which vertex to visit next
    vStack.push(0);     // Push first vertex on stack

    while (!vStack.empty())
    {
        int current = vStack.top();   // Get top vertex
        vStack.pop();                 // Pop vertex off the stack

        // Visit the unvisited node
        if (this->vertices[current].visited == false)
        {
            this->vertices[current].visited = true;     // Mark the vertex as visited
        }

        // Push current vertex's unvisited neighbors onto stack to be visited next
        for (int i = 0; i < (int)this->adjList[current].size(); ++i)
        {
            int neighbor = this->adjList[current][i].to_vertex;  // Get neighbor vertex

            // Case of unvisited vertex:
            if (this->vertices[neighbor].visited == false)
            {
                vStack.push(neighbor);                     // Push neighbor onto stack
                this->vertices[neighbor].prev = current;   // Set neighbors prev to current vertex
            }

            // Since vertex has already been visited check if it is an ancestor of the current vertex
            else if (this->vertices[neighbor].visited == true)
            {
                // Make sure neighbor is an ancestor of the current vertex and not the prev vertex
                if (this->vertices[current].prev != neighbor)
                {   
                    return true;  // The graph contains a cycle
                }
            }
        }
    }

    return false;  // A cycle could not be found
}

/**
 * @brief Purpose: Print the graph
 */
void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++)
    {
        // Print each list of edges in the adjacency list
        cout << i << ": ";
        for(auto j = adjList[i].begin(); j != adjList[i].end(); ++j)
        {
            cout << (*j).to_vertex << " " ;
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Purpose: Finds the shortest path between 2 cities using Djikstras Algorithm
 * @param start: Starting vertex
 * @param end: Ending vertex
 * @param &distance: Distance of the shortest path, is returned by reference 
 * @return vector<vertex>: The path taken to get from start to end
 */
vector<Vertex> Graph::dijkstraAlgorithm(Vertex start, Vertex end, double& distance)
{
    Heap priorityQueue;  // Stores vertices with priority based on distance from start.

    // Set all vertices to have infinite distance and no prev vertex
    for (Vertex& v : this->vertices)
    {
        v.distance = numeric_limits<double>::infinity();
        v.prev = -1;
        v.visited = false;
    }

    // Find the starting vertex in the graph and insert it into the priority queue
    for (Vertex& v : this->vertices)
    {
        // If the starting vertex is found
        if (v.id == start.id)
        {
            v.distance = 0;            // Starting vertex has distance of 0
            priorityQueue.insert(v);   // Insert starting vertex into priority queue
        }
    }

    // While the queue is not empty
    while (priorityQueue.get_count() > 0)
    {
        Vertex current = priorityQueue.removeMin();  // Get vertex with minimum distance from start
        this->vertices[current.id].visited = true;   // Mark it as visited indicating shortest path has been found

        // For each neighbor of vertex current calculate distance and insert neighbor into the queue
        for (int i = 0; i < (int)this->adjList[current.id].size(); ++i)
        {
            Vertex& neighbor = vertices[adjList[current.id][i].to_vertex];          // Get currents neighbor
            
            double newDistance = current.distance + adjList[current.id][i].weight;  // Calculate distance to neighbor using the current vertex and edge weight

            // If the shortest path has not yet been found for neighbor
            if (neighbor.visited == false)
            {
                // If the new path to the neighbor is shorter
                if (newDistance < neighbor.distance)
                {
                    // Update the previous vertex and distance
                    neighbor.prev = current.id;
                    neighbor.distance = newDistance;

                    Vertex* verticesInQueue = priorityQueue.get_heaparray();  // Used to get vertices inside the priority queue
                    bool existInQueue = false;                                // Used to check if a vertex exist in the priority queue
                    int position = 0;                                         // Used to track a verticies position in the priority queue
                
                    // Check to see if the neighbor is already in the queue, if it exist get its position
                    for (int i = 0; i < priorityQueue.get_count(); ++i)
                    {
                        Vertex v = verticesInQueue[i];  // Get current vertex

                        // If it matches with neighbor, get its position in the queue
                        if (neighbor.id == v.id)
                        {
                            existInQueue = true;
                            position = i;
                        }
                    }

                    // If the vertex is already in the priority queue update its priority with the new distance
                    if (existInQueue)
                    {
                        priorityQueue.changeKey(position, neighbor.distance);  // Update priority of the neighbor
                    }
                    // Otherwise insert it into the priority queue
                    else
                    {
                        priorityQueue.insert(neighbor);
                    }
                }
            }
        }
    }

    // After the loop the shortest path has been calculated

    vector<Vertex> shortestPath;  // Used to return the shortest path
    vector<Vertex> temp;          // Used to store the shortest path in reverse order

    // Get the end vertex from vertex list
    for (Vertex v : vertices)
    {
        // If the end vertex is found
        if (v.id == end.id)
        {
            temp.push_back(v);       // Put it in the temp list
            distance = v.distance;   // Set distance to be returned by reference
        }
    }
    int previous = temp[0].prev;  // Used to store index of previous vertex, is set to prev of end vertex
    
    // Fill the temporary list with the shortest path in reverse order until the starting vertex is reached
    while (previous != -1)
    {
        temp.push_back(vertices[previous]);  // Insert the current vertex
        previous = vertices[previous].prev;  // Get the previous vertex
    }

    // Use the path in reverse order to fill the vector with the path in order
    for (int i = temp.size() - 1; i >= 0; --i)
    {
        shortestPath.push_back(temp[i]);
    }

    return shortestPath;  // Return the shortest path from start to end
}
