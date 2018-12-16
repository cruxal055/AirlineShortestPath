#include "dijkstra.h"

dijkstra::dijkstra(QString fileName)
{
    QFile reader(fileName);
    reader.open(QIODevice::ReadOnly);
    QXmlStreamReader streamer;
    streamer.setDevice(&reader);
    while(!streamer.atEnd() && streamer.readNextStartElement())
    {
        if(streamer.name() == "FLIGHT")
        {
            airline temp;
            airport temp1, temp2;
            streamer.readNextStartElement();
            string tempo = streamer.readElementText().toStdString();
            if(tempo == "\\N")
            {
                for(int i = 0; i < 7; ++i)
                {
                    streamer.readNextStartElement();
                    streamer.readElementText().toStdString();
                }
                continue;
            }
            temp.airlineID = std::stoi(tempo);
            streamer.readNextStartElement();
            temp.airName = streamer.readElementText().toStdString();
            streamer.readNextStartElement();
            temp1.code = std::stoi(streamer.readElementText().toStdString());
            streamer.readNextStartElement();
            temp1.name = (streamer.readElementText().toStdString());
            allVertex[temp1.code] = temp1.name;
            streamer.readNextStartElement();
            temp2.code = std::stoi(streamer.readElementText().toStdString());
            streamer.readNextStartElement();
            temp2.name = (streamer.readElementText().toStdString());
            allVertex[temp2.code] = temp2.name;
            streamer.readNextStartElement();
            double dist = (streamer.readElementText().toDouble());
            graph[temp1.code].push_back(flight(temp,pair<int,double>(temp2.code,dist)));
            streamer.readNextStartElement();
        }
    }
    reader.close();
    resetShortestPaths();
}


void dijkstra::findShortest(int code, int end)
{
    if(!allVertex.count(code) || !allVertex.count(end))
        throw airportDNE;
    else
    {
        airport temp = airport(allVertex[code],code);
        perform(temp.code);
    }
}

dijkstra::~dijkstra()
{
    allVertex.clear();
}

void dijkstra::resetShortestPaths()
{
    map<int,string>::iterator it1  = allVertex.begin();
    index temp;
    for(;it1 != allVertex.end(); ++it1)
        fastest[it1->first] = temp;
}


void dijkstra::perform(int airportIndex)
{
    bool visited[MAX];
    struct::index currentItem;
    resetShortestPaths();
    for(int i = 0; i < MAX; ++i)
        visited[i] = false;
    fastest[airportIndex].distance = 0;
    fastest[airportIndex].currentVertex = airportIndex;
    priority_queue<struct::index,vector<struct::index>,compareThem> pq;
    pq.push(fastest[airportIndex]);
    while(!pq.empty())
    {
        currentItem = pq.top();
        pq.pop();
        double vertexWeight = currentItem.distance;
        unsigned int size = graph[currentItem.currentVertex].size();
        if(visited[currentItem.currentVertex])
            continue;
        for(int i = 0; i < size; ++i)
        {
            double currentWeight = graph[currentItem.currentVertex][i].second.second;

            if(!visited[ graph[currentItem.currentVertex][i].second.first])
            {
                int pos = graph[currentItem.currentVertex][i].second.first;
                if(vertexWeight + currentWeight <= fastest[pos].distance)
                {

                    struct::index tempItem;
                    tempItem.companies.push_back(graph[currentItem.currentVertex][i].first);
                    tempItem.currentVertex = pos;
                    tempItem.lastVertex = currentItem.currentVertex;
                    tempItem.distance = vertexWeight + currentWeight;
                    if(vertexWeight + currentWeight == fastest[pos].distance)
                        (fastest[pos].interestingCopy(tempItem));
                    else
                        ( fastest[pos] = tempItem);


                    pq.push(fastest[pos]);
                }

            }
        }
        visited[currentItem.currentVertex] = true;
    }
}

/*QString dijkstra::displayItineraries(int beginning, int end)
{
    QString itinerary;
    stack<index> reverseOrder;
    while(end != beginning)
    {
        reverseOrder.push(fastest[end]);
        end = fastest[end].lastVertex;
    }
    double totalDistance = 0;
    while(!reverseOrder.empty())
    {
        index temp = reverseOrder.top();
        itinerary.append("Take airline: " + QString::fromStdString(temp.company.airName) + " at " +
                         QString::fromStdString(allVertex[temp.lastVertex]) + " and fly to " +
                         QString::fromStdString(allVertex[temp.currentVertex]) + " for " +
                         QString::number(temp.distance - totalDistance) + " miles \n\n");
        totalDistance = temp.distance;
        reverseOrder.pop();
    }
    return itinerary;
}*/

void dijkstra::displayItinerary(QTextEdit *textBox, int start, int end)
{
    stack<index> reverseOrder;
    while(end != start)
    {
        reverseOrder.push(fastest[end]);
        end = fastest[end].lastVertex;
    }
    double totalDistance = 0;
    while(!reverseOrder.empty())
    {
        QString line = "";
        index temp = reverseOrder.top();
        line.append("Fly from " + QString::fromStdString(allVertex[temp.lastVertex]) + " to "
                    + QString::fromStdString(allVertex[temp.currentVertex]) + " for " +
                    QString::number(temp.distance - totalDistance) + " miles ");
        line.append("with airlines: ");
        for(int i = 0; i < temp.companies.size(); ++i)
            line.append(QString::fromStdString(temp.companies[i].airName) + ", ");
        textBox->append(line + "\n");
        reverseOrder.pop();
    }
}

void dijkstra::printItinerary(string fileName, int start, int end)
{
    ofstream out(fileName);
    stack<index> reverseOrder;
    while(end != start)
    {
        reverseOrder.push(fastest[end]);
        end = fastest[end].lastVertex;
    }
    double totalDistance = 0;
    while(!reverseOrder.empty())
    {
        index temp = reverseOrder.top();
        out<<"Fly from "<<allVertex[temp.lastVertex]<<" to "<<allVertex[temp.currentVertex]
           <<" for "<<temp.distance - totalDistance<<" miles with airlines: ";
        for(int i = 0; i < temp.companies.size(); ++i)
            out<<temp.companies[i].airName<<", ";
        out<<endl;
        reverseOrder.pop();
    }
    out.close();
}
