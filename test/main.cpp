#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
//#include "heap.h"
using namespace std;

int main(int argc, char* argv[])
{
    // Header
    cout << "Author: Sarah Turner, Erin Nichole Bailey, Ryan Bebereia" << endl;
    cout << "Date: 11/29/2023" << endl;
    cout << "Course: CS 311 (Data Structures and Algorithms)" << endl;
    cout << "Description: Program to find the shortest route between cities" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    ifstream infile;
    Graph cityGraph;

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
            
            
            Vertex city;
            city.id = id;
            city.cityCode = cityCode;
            city.name = cityName;
            city.population = population;
            city.elevation = elevation;
            cityGraph.addVertex(city);
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
            cityGraph.addDirectedEdge(fromCity, toCity, distance);
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
        for (int i = 0; i < cityGraph.vertices.size(); i++){ //Ryan
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
        if (valid1 == false ){
            cout << "Invalid City Code: " << abb1; //Ryan
        }
        if (valid2 == false ){
            cout << "Invalid City Code: " << abb2; //Ryan
        }

    double tempDistance = 0;
    vector<Vertex> newcitypath;
    newcitypath = cityGraph.djikstraAlgorithm(cityGraph.vertices[index1], cityGraph.vertices[index2], tempDistance);

    return 0;
}
