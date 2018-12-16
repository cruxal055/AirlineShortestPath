#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <string>
#include <set>
#include "airport.h"
#include <queue>
#include <limits>
#include <QXmlStreamReader>
#include <QFile>
#include <qiodevice.h>
#include "airline.h"
#include <cmath>
#include <stack>
#include <utility>
#include <iostream>
#include "index.h"
#include <QTextEdit>
#include <fstream>

using namespace std;

#define MAX 100001
#define u_int unsigned int

#define flight pair<airline, pair<int, double> >
#define route pair<airport, double>
#define dbl_max numeric_limits<double>::max()
#define int_max numeric_limits<int>::max()

class dijkstra
{
    public:
        dijkstra(QString fileName);
        ~dijkstra();

       void findShortest(int code, int end);
       void perform(int airportIndex);
       void displayResults(int begining, int end);
       void displayItinerary(QTextEdit *textBox, int start, int end);
       void printItinerary(string fileName, int start, int end);

    private:
        map<int, string> allVertex;
        index fastest[MAX];
        vector<index> otherRoutes[MAX];
        vector<pair<airline, pair<int,double>>> graph[MAX]; //each index is an airport which each vector is a flight
        u_int numOfAirports;
        u_int verticies, edges, starting;
        void resetShortestPaths();
};

#endif // DIJKSTRA_H
