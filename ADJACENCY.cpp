
/* 
NAME: KANISHKA SHROTIYA
PRN: 1032233553
PANEL J-2
*/

#include <iostream>
#include <string>
using namespace std;

class Friend {
public:
    string name;
    int id;
    Friend* next;

    Friend(string n = "", int i = 0) : name(n), id(i), next(NULL) {}
};

class Stack {
private:
    int arr[20];
    int top;

public:
    Stack() : top(-1) {}

    void push(int val) {
        if (top < 19)
            arr[++top] = val;
    }

    int pop() {
        return (top >= 0) ? arr[top--] : -1;
    }

    bool isEmpty() {
        return top == -1;
    }
};

class Queue {
private:
    int arr[20];
    int front, rear;

public:
    Queue() : front(0), rear(0) {}

    void enqueue(int val) {
        if (rear < 20)
            arr[rear++] = val;
    }

    int dequeue() {
        return (front < rear) ? arr[front++] : -1;
    }

    bool isEmpty() {
        return front == rear;
    }
};

class Graph {
private:
    int n;
    Friend* head[20];
    bool visited[20];

public:
    Graph() {
        cout << "Enter the number of friends (less than 20): ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            head[i] = new Friend;
            cout << "Enter Name: ";
            cin >> head[i]->name;
            cout << "Enter ID: ";
            cin >> head[i]->id;
            head[i]->next = NULL;
            visited[i] = false;
        }
    }

    void AdjacencyList();
    void display();
    void NonRecDFT();
    void RecursiveDFT(int current);
    void IterativeBFS(int startFriendIndex);
};

void Graph::AdjacencyList() {
    for (int i = 0; i < n; i++) {
        Friend* temp = head[i];
        cout << "Friend " << temp->name << " (ID: " << temp->id << ") has the following adjacent friends:" << endl;
        char choice;

        do {
            Friend* adjtemp = new Friend;
            cout << "Enter the name of adjacent friend: ";
            cin >> adjtemp->name;
            cout << "Enter ID of adjacent friend: ";
            cin >> adjtemp->id;
            adjtemp->next = temp->next;
            temp->next = adjtemp;
            cout << "Do you want to add another adjacent friend for " << temp->name << " (y/n)? ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }
}

void Graph::display() {
    for (int i = 0; i < n; i++) {
        Friend* temp = head[i];
        cout << "Friend " << temp->name << " (ID: " << temp->id << ") has the following adjacent friends:" << endl;
        temp = temp->next;
        while (temp != NULL) {
            cout << "  " << temp->name << " (ID: " << temp->id << ")" << endl;
            temp = temp->next;
        }
    }
}

void Graph::RecursiveDFT(int current) {
    visited[current] = true;
    cout << "Visited: " << head[current]->name << " (ID: " << head[current]->id << ")" << endl;
    Friend* temp = head[current]->next;
    while (temp != NULL) {
        int adjIndex = -1;
        for (int i = 0; i < n; i++) {
            if (head[i]->name == temp->name) {
                adjIndex = i;
                break;
            }
        }
        if (adjIndex != -1 && !visited[adjIndex]) {
            RecursiveDFT(adjIndex);
        }
        temp = temp->next;
    }
}

void Graph::NonRecDFT() {
    Stack s;
    fill(visited, visited + n, false);
    s.push(0);

    while (!s.isEmpty()) {
        int current = s.pop();
        if (!visited[current]) {
            visited[current] = true;
            cout << "Visited: " << head[current]->name << " (ID: " << head[current]->id << ")" << endl;
            Friend* temp = head[current]->next;
            while (temp != NULL) {
                int adjIndex = -1;
                for (int i = 0; i < n; i++) {
                    if (head[i]->name == temp->name) {
                        adjIndex = i;
                        break;
                    }
                }
                if (adjIndex != -1 && !visited[adjIndex]) {
                    s.push(adjIndex);
                }
                temp = temp->next;
            }
        }
    }
}

void Graph::IterativeBFS(int startFriendIndex) {
    fill(visited, visited + n, false);
    Queue q;
    visited[startFriendIndex] = true;
    q.enqueue(startFriendIndex);

    cout << "Breadth First Traversal starting from " << head[startFriendIndex]->name 
         << " (ID: " << head[startFriendIndex]->id << "):" << endl;

    while (!q.isEmpty()) {
        int currentFriendIndex = q.dequeue();
        cout << head[currentFriendIndex]->name << " (ID: " << head[currentFriendIndex]->id << ") ";

        Friend* temp = head[currentFriendIndex]->next;
        while (temp != NULL) {
            int adjFriendIndex = -1;
            for (int i = 0; i < n; i++) {
                if (head[i]->name == temp->name && head[i]->id == temp->id) {
                    adjFriendIndex = i;
                    break;
                }
            }
            if (adjFriendIndex != -1 && !visited[adjFriendIndex]) {
                visited[adjFriendIndex] = true;
                q.enqueue(adjFriendIndex);
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

int main() {
    Graph g;
    int choice;
    do {
        cout << "\nMenu: \n";
        cout << "1. Enter Friend Adjacency List\n";
        cout << "2. Display Friend Network\n";
        cout << "3. Perform Non-Recursive Depth-First Traversal\n";
        cout << "4. Perform Iterative Breadth-First Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.AdjacencyList();
                break;
            case 2:
                g.display();
                break;
            case 3:
                cout << "Depth-First Traversal starting from all unvisited nodes:" << endl;
                g.NonRecDFT();
                break;
            case 4:
                cout << "Enter starting friend index for BFS: ";
                int startIndex;
                cin >> startIndex;
                g.IterativeBFS(startIndex);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
