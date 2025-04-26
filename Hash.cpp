#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

class record {
    int rollno, marks;
    string name;

public:
    record() : rollno(-1), marks(0), name("") {}
    friend class student;
};

class hashing {
    int rollno, pos;

public:
    hashing() {
        rollno = -1;
        pos = -1;
    }
    friend class student;
};

class student {
    record recs[TABLE_SIZE];
    hashing h[TABLE_SIZE];

public:
    student() {}

    void create_withoutrp();
    void create_withrp();
    void retrieve();
    void display();

private:
    int hash(int key) {
        return key % TABLE_SIZE;
    }

    void insert_withoutrp(record rec) {
        int pos = hash(rec.rollno);
        int originalPos = pos;

        while (h[pos].rollno != -1) {
            cout << "Collision detected at index " << pos << " for roll no " << rec.rollno << endl;
            pos = (pos + 1) % TABLE_SIZE;
            if (pos == originalPos) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        h[pos].rollno = rec.rollno;
        h[pos].pos = pos;
        recs[pos] = rec;
    }

    void insert_withrp(record rec) {
        int pos = hash(rec.rollno);
        int originalPos = pos;

        if (h[pos].rollno == -1) {
            h[pos].rollno = rec.rollno;
            h[pos].pos = pos;
            recs[pos] = rec;
            return;
        }

        if (hash(h[pos].rollno) == pos) {
            while (h[pos].rollno != -1) {
                cout << "Collision detected at index " << pos << " for roll no " << rec.rollno << endl;
                pos = (pos + 1) % TABLE_SIZE;
                if (pos == originalPos) {
                    cout << "Hash table is full!" << endl;
                    return;
                }
            }
            h[pos].rollno = rec.rollno;
            h[pos].pos = pos;
            recs[pos] = rec;
        } else {
            record temp = recs[pos];
            h[pos].rollno = rec.rollno;
            h[pos].pos = pos;
            recs[pos] = rec;
            insert_withoutrp(temp);
        }
    }
};

void student::create_withoutrp() {
    int size;
    cout << "Enter number of records to insert without replacement: ";
    cin >> size;

    fstream f("hash_table.txt", ios::out | ios::app);
    if (!f.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        record rec;
        cout << "Enter Roll No: ";
        cin >> rec.rollno;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, rec.name);
        cout << "Enter Marks: ";
        cin >> rec.marks;

        insert_withoutrp(rec);
        f << rec.rollno << " " << rec.name << " " << rec.marks << endl;
    }

    f.close();
}

void student::create_withrp() {
    int size;
    cout << "Enter number of records to insert with replacement: ";
    cin >> size;

    fstream f("hash_table.txt", ios::out | ios::app);
    if (!f.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        record rec;
        cout << "Enter Roll No: ";
        cin >> rec.rollno;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, rec.name);
        cout << "Enter Marks: ";
        cin >> rec.marks;

        insert_withrp(rec);
        f << rec.rollno << " " << rec.name << " " << rec.marks << endl;
    }

    f.close();
}

void student::retrieve() {
    int key;
    cout << "Enter Roll No to search: ";
    cin >> key;

    int pos = hash(key);
    int originalPos = pos;

    while (h[pos].rollno != -1) {
        if (h[pos].rollno == key) {
            cout << "Record Found:\n";
            cout << "Roll No: " << recs[pos].rollno << "\nName: " << recs[pos].name << "\nMarks: " << recs[pos].marks << endl;
            return;
        }
        pos = (pos + 1) % TABLE_SIZE;
        if (pos == originalPos) break;
    }

    cout << "Record not found.\n";
}

void student::display() {
    cout << "\nHash Table:\n";
    cout << "Index\tRoll No\tName\t\tMarks\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (h[i].rollno != -1) {
            cout << i << "\t" << recs[i].rollno << "\t" << recs[i].name << "\t\t" << recs[i].marks << endl;
        }
    }
}

int main() {
    student s;
    int choice;

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Insert records without replacement\n";
        cout << "2. Insert records with replacement\n";
        cout << "3. Display Hash Table\n";
        cout << "4. Retrieve a record\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.create_withoutrp();
                break;
            case 2:
                s.create_withrp();
                break;
            case 3:
                s.display();
                break;
            case 4:
                s.retrieve();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
