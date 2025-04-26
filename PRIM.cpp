/* 
NAME: KANISHKA SHROTIYA
PRN: 1032233553
PANEL J-2
*/

#include <iostream>
#include <string>
#define max 20
using namespace std;

class graph
{
    int cost[max][max];
    string cityNames[max];
    int cities;

public:
    graph()
    {
        cout << "Enter the number of cities: ";
        cin >> cities;
        cin.ignore();

        for (int i = 0; i < cities; i++)
        {
            cout << "Enter name of city " << i + 1 << ": ";
            getline(cin, cityNames[i]);
        }

        for (int i = 0; i < cities; i++)
        {
            for (int j = 0; j < cities; j++)
            {
                if (i == j)
                    cost[i][j] = 0;
                else
                    cost[i][j] = 999;
            }
        }
    }

    void create();
    void display();
    void primAlg(int startVertex);
    int getCities() 
    {
        return cities;
    } 
    string getCityName(int index) {
        return cityNames[index];
    }
};

void graph::create()
{
    char ch;
    for (int i = 0; i < cities; i++)
    {
        for (int j = i + 1; j < cities; j++)
        {
            cout << "Is there a connection between " << cityNames[i] << " and " << cityNames[j] << "? (y/n): ";
            cin >> ch;

            if (ch == 'y' || ch == 'Y')
            {
                int distance;
                cout << "Enter the distance between " << cityNames[i] << " and " << cityNames[j] << ": ";
                cin >> distance;
                cost[i][j] = distance;
                cost[j][i] = distance;
            }
        }
    }
}

void graph::display()
{
    cout << "\nAdjacency Matrix:\n";

    for (int i = 0; i < cities; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            if (cost[i][j] == 999)
                cout << "∞ ";
            else
                cout << cost[i][j] << " ";
        }
        cout << endl;
    }
}



void graph::primAlg(int startVertex)
{
    int nearest[max];
    int minCost = 0;
    bool visited[max] = {};
    int edgeCount = 0;

    for (int i = 0; i < cities; i++)
    {
        if (i != startVertex)
            nearest[i] = startVertex;
        else
            nearest[i] = -1;
    }

    visited[startVertex] = true;

    cout << "\nEdges in the Minimum Spanning Tree:\n";

    for (int i = 0; i < cities - 1; i++)
    {
        int min = 999, j = -1;

        for (int k = 0; k < cities; k++)
        {
            if (!visited[k] && nearest[k] != -1 && cost[k][nearest[k]] < min)
            {
                min = cost[k][nearest[k]];
                j = k;
            }
        }

        if (j == -1)
            break;

        cout << cityNames[nearest[j]] << " -> " << cityNames[j] << " (Distance: " << min << ")\n";
        minCost += min;
        visited[j] = true;
        nearest[j] = -1;
        edgeCount++;

        for (int k = 0; k < cities; k++)
        {
            if (!visited[k] && cost[k][j] < cost[k][nearest[k]])
                nearest[k] = j;
        }
    }

    cout << "\nTotal cost of the Minimum Spanning Tree: " << minCost << endl;

    if (edgeCount < cities - 1)
    {
        cout << "Warning: The graph is disconnected, so a full MST was not formed!" << endl;
    }
}

int main()
{
    graph g;
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Minimum Spanning Tree using Prim's Algorithm\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            g.create();
            break;
        case 2:
            g.display();
            break;
        case 3:
        {
            string startCity;
            cout << "\nEnter the starting city: ";
            cin.ignore();
            getline(cin, startCity);

            int startVertex = -1;
            for (int i = 0; i < g.getCities(); i++)
            {
                if (g.getCityName(i) == startCity)
                {
                    startVertex = i;
                    break;
                }
            }

            if (startVertex == -1)
            {
                cout << "Invalid starting city!" << endl;
            }
            else
            {
                g.primAlg(startVertex);
            }
            break;
        }
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}