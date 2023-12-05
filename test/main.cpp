#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

int main(int argc, char* argv[])
{
    // Header
    cout << "Author: Sarah Turner, " << endl;
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
            cout << "Getting input: \n";
            infile >> id;
            cout << "Id: " << id << endl;
            infile >> cityCode;
            cout << "CC: " << cityCode << endl;
            infile >> cityName;
            cout << "Name: " << cityName << endl;
            infile >> population;
            cout << "Population: " << population << endl;
            infile >> elevation;
            cout << "Elevation: " << elevation << endl;
            
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

    // Read edges from input file (roads)
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

    return 0;
}