#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
//#include "heap.h"
using namespace std;

bool notInVector(int val, vector<int> vec);

int main(int argc, char* argv[])
{
    // Header
    cout << "Author: Sarah Turner, Erin Nichole Bailey, Ryan Bebereia" << endl;
    cout << "Date: 11/29/2023" << endl;
    cout << "Course: CS 311 (Data Structures and Algorithms)" << endl;
    cout << "Description: Program to find the shortest route between cities" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    ifstream infile;
    Graph cityGraph;    // empty graph

    // Read vertices from input file (cities)
    infile.open("city.txt");
    if (!infile)
    {
        cout << "Could not open file: city.txt" << endl;
    }
    else
    {
        int id;
        string cityCode;
        string cityName;
        int population;
        int elevation;

        while (infile)
        {
            // uncomment couts for testing
            //cout << "Getting input: \n";
            infile >> id;
            //cout << "Id: " << id << endl;
            infile >> cityCode;
            if (cityCode.length() != 2 || cityCode[0] < 65 || cityCode[0] > 90 || cityCode[1] < 65 || cityCode[1] > 90){ //Ryan
                cout << "not valid"; //Ryan
            } //Ryan
            //cout << "CC: " << cityCode << endl;
            infile >> cityName;
            //cout << "Name: " << cityName << endl;
            infile >> population;
            //cout << "Population: " << population << endl;
            infile >> elevation;
            //cout << "Elevation: " << elevation << endl;
            
            // construct a vertex from read data
            Vertex city(id, cityCode, cityName, population, elevation, -1, false, 0.0);
            /*
            city.id = id;
            city.cityCode = cityCode;
            city.name = cityName;
            city.population = population;
            city.elevation = elevation;
            */
           
            // add vertex to graph
            if(infile) cityGraph.addVertex(city);
        }
    }
    infile.close();
 
    infile.open("road.txt");
    if (!infile)
    {
        cout << "Could not open file: road.txt" << endl;
    }
    else
    {
        int fromCity;
        int toCity;
        float distance;
        while (infile)
        {
            infile >> fromCity;
            infile >> toCity;
            infile >> distance;
            if(infile) cityGraph.addDirectedEdge(fromCity, toCity, distance);
        }
    }

    // Read edges from input file (roads)
    int counter = 0; //Ryan
    string abb1 = argv[1];
    string abb2 = argv[2];
    bool valid1 = false;
    bool valid2 = false;
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < (int)cityGraph.vertices.size(); i++){ //Ryan
        counter++;
        if (abb1 == cityGraph.vertices[i].cityCode){
            valid1 = true;
            index1 = i;
        }
        if (abb2 == cityGraph.vertices[i].cityCode){
            valid2 = true;
            index2 = i;
        }
        if (valid1 == true && valid2 == true){
            break;
        }   
    } //Ryan
    if (valid1 == false && valid2 == true){
        cout << "Invalid City Code: " << abb1 << endl; //Ryan
    }else if (valid2 == false && valid1 == true){
        cout << "Invalid City Code: " << abb2 << endl; //Ryan
    }else if (valid1 == false && valid2 == false){
        cout << "Invalid City Codes: " << abb1 << " and " << abb2 << endl;
    }
    if(valid1 == false || valid2 == false){
        cout << "usage: prog9 city_code1 city_code2" << endl;
        cout << "valid city codes follow:" << endl;
        for(int i = 0; i < (int)cityGraph.vertices.size(); i++){
            cout << cityGraph.vertices.at(i).cityCode << endl;
        }
        return 0;
    } // at this point if the program is still running we have two valid city codes
    // now checking a path exists between the two cities

    vector<int> BFS = cityGraph.BreadthFirstSearch(index1);

    if(notInVector(index2, BFS)){
        cout << "No route from " << cityGraph.vertices.at(index1).name << " to " << cityGraph.vertices.at(index2).name << endl;
        cout << "usage: prog9 city_code1 city_code2" << endl;
        cout << "valid city codes follow:" << endl;
        for(int i = 0; i < (int)cityGraph.vertices.size(); i++){
            cout << cityGraph.vertices.at(i).cityCode << endl;
        }
        return 0;
    }// if program has survived, the two city codes exist in the graph AND a path exists between them.

    cout << "From City: " << cityGraph.vertices.at(index1).name << ", population " << cityGraph.vertices.at(index1).population << ", elevation " << cityGraph.vertices.at(index1).elevation << endl;
    cout << "From City: " << cityGraph.vertices.at(index2).name << ", population " << cityGraph.vertices.at(index2).population << ", elevation " << cityGraph.vertices.at(index2).elevation << endl;
        

    double tempDistance = 0;
    vector<Vertex> newcitypath;
    newcitypath = cityGraph.dijkstraAlgorithm(cityGraph.vertices[index1], cityGraph.vertices[index2], tempDistance);

    cout << "The shortest distance from " << cityGraph.vertices.at(index1).name << " to " << cityGraph.vertices.at(index2).name << " is " << tempDistance << " through the route:" ;

    cout << newcitypath.at(0).name; 
    for(int i = 1; i < (int)newcitypath.size(); i++){
        cout << "->" << newcitypath.at(i).name; 
    }
    cout << endl;
    
    /*
    Graph map;
    Vertex A(0, "A", "", 0, 0,-1, false, 0.0);
    Vertex B(1, "B", "", 0, 0,-1, false, 0.0);
    Vertex C(2, "C", "", 0, 0,-1, false, 0.0);
    Vertex D(3, "D", "", 0, 0,-1, false, 0.0);
    Vertex E(4, "E", "", 0, 0,-1, false, 0.0);
    map.addVertex(A);
    map.addVertex(B);
    map.addVertex(C);
    map.addVertex(D);
    map.addVertex(E);

    map.addUndirectedEdge(0, 1, 1);
    map.addUndirectedEdge(0, 3, 2);
    map.addUndirectedEdge(1, 2, 5);
    map.addUndirectedEdge(1, 4, 3);
    map.addUndirectedEdge(2, 4, 4);

    double distance = 0.0;
    vector<Vertex> shortPath = map.djikstraAlgorithm(A, C, distance);

    for(int i = 0; i < (int)shortPath.size(); i++){
        cout << shortPath.at(i).cityCode << " " ;
    }
    cout << endl;
    */

    return 0;
}

bool notInVector(int val, vector<int> vec){
    for(int i = 0; i < (int)vec.size(); i++){
        if(vec.at(i) == val) return false;
    }
    return true;
}

