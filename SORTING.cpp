/* 
NAME: KANISHKA SHROTIYA
PRN: 1032233553
PANEL J-2
*/

#include <iostream>
#include <string>
using namespace std;

int n;

class MobileUser {
    int number;
    int bill;
    string name;

public:
    MobileUser() {
        number = 0;
        bill = 0;
        name = "";
    }
    friend class Records;
};

// Stack class for iterative sorting (no pointers)
class Stack {
    int arr[20]; // max 5 users → 2*n = 10 elements, so 20 is safe
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(int val) {
        if (top < 19) {
            arr[++top] = val;
        }
    }

    int pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return -1;
    }

    bool isEmpty() {
        return top == -1;
    }
};

class Records {
    MobileUser user[5];

public:
    void Accept();
    void Display();
    int BinarySearch(int key);
    int RecursiveBinarySearch(int low, int high, int key);
    void QuickSortRecursive(int low, int high);
    int Partition(int l, int h);
    void QuickSortIterative(int l, int h);
    void LinearSearch(int choice, int key, string key1 = "");
    void Adjust(int n1, int i);
    void HeapSort();
};

void Records::Accept() {
    cout << "Enter the details for each user:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "User " << (i + 1) << ":" << endl;

        cout << "Enter name: ";
        cin >> user[i].name;

        cout << "Enter phone number: ";
        cin >> user[i].number;

        cout << "Enter bill amount: ";
        cin >> user[i].bill;

        cout << endl;
    }
}

void Records::Display() {
    cout << "Displaying user details:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "User " << (i + 1) << ":" << endl;
        cout << "Name: " << user[i].name << endl;
        cout << "Phone Number: " << user[i].number << endl;
        cout << "Bill Amount: " << user[i].bill << endl;
        cout << endl;
    }
}

int Records::BinarySearch(int key) {
    int low = 0, high = n - 1;
    int passes = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        passes++;

        if (user[mid].number == key)
            return mid;

        if (user[mid].number < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    cout << "Searches = " << passes << endl;
    return -1;
}

int Records::RecursiveBinarySearch(int low, int high, int key) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        if (user[mid].number == key)
            return mid;

        if (user[mid].number > key)
            return RecursiveBinarySearch(low, mid - 1, key);
        else
            return RecursiveBinarySearch(mid + 1, high, key);
    }
    return -1;
}

int Records::Partition(int low, int high) {
    int pivot = user[high].number;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (user[j].number <= pivot) {
            i++;
            swap(user[i], user[j]);
        }
    }
    swap(user[i + 1], user[high]);
    return i + 1;
}

void Records::QuickSortRecursive(int low, int high) {
    if (low < high) {
        int pi = Partition(low, high);
        QuickSortRecursive(low, pi - 1);
        QuickSortRecursive(pi + 1, high);
    }
}

void Records::QuickSortIterative(int low, int high) {
    Stack stk;
    stk.push(low);
    stk.push(high);

    while (!stk.isEmpty()) {
        high = stk.pop();
        low = stk.pop();

        int p = Partition(low, high);

        if (p - 1 > low) {
            stk.push(low);
            stk.push(p - 1);
        }
        if (p + 1 < high) {
            stk.push(p + 1);
            stk.push(high);
        }
    }
}

void Records::LinearSearch(int choice, int key, string key1) {
    int passes = 0;
    if (choice == 1) {
        for (int i = 0; i < n; i++) {
            passes++;
            if (user[i].number == key) {
                cout << "Record found:" << endl;
                cout << "Name: " << user[i].name << endl;
                cout << "Phone Number: " << user[i].number << endl;
                cout << "Bill Amount: " << user[i].bill << endl;
                cout << "Passes = " << passes << endl;
                return;
            }
        }
        cout << "Record not found." << endl;
    } else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            passes++;
            if (user[i].bill == key) {
                cout << "Record found:" << endl;
                cout << "Name: " << user[i].name << endl;
                cout << "Phone Number: " << user[i].number << endl;
                cout << "Bill Amount: " << user[i].bill << endl;
                cout << "Passes = " << passes << endl;
                return;
            }
        }
        cout << "Record not found." << endl;
    } else if (choice == 3) {
        for (int i = 0; i < n; i++) {
            passes++;
            if (user[i].name == key1) {
                cout << "Record found:" << endl;
                cout << "Name: " << user[i].name << endl;
                cout << "Phone Number: " << user[i].number << endl;
                cout << "Bill Amount: " << user[i].bill << endl;
                cout << "Passes = " << passes << endl;
                return;
            }
        }
        cout << "Record not found." << endl;
    }
}

void Records::Adjust(int n1, int i) {
    int j;
    MobileUser temp;
    while ((2 * i + 1) <= n1) {
        j = 2 * i + 1;
        if ((j + 1 <= n1) && (user[j + 1].number > user[j].number))
            j++;
        if (user[i].number >= user[j].number)
            break;
        else {
            temp = user[i];
            user[i] = user[j];
            user[j] = temp;
            i = j;
        }
    }
}

void Records::HeapSort() {
    int x = n, passes = 0;

    for (int i = (x / 2) - 1; i >= 0; i--) {
        Adjust(x - 1, i);
    }

    while (x > 0) {
        MobileUser temp = user[0];
        user[0] = user[x - 1];
        user[x - 1] = temp;
        x--;
        passes++;
        Adjust(x - 1, 0);
    }

    cout << "Passes = " << passes << endl;
}

int main() {
    Records records;
    cout << "Enter the number of users (max 5): ";
    cin >> n;

    if (n > 5 || n <= 0) {
        cout << "Invalid number of users. Please enter a number between 1 and 5." << endl;
        return 0;
    }

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Accept Records" << endl;
        cout << "2. Display Records" << endl;
        cout << "3. Binary Search" << endl;
        cout << "4. Recursive Binary Search" << endl;
        cout << "5. Quick Sort (Recursive)" << endl;
        cout << "6. Quick Sort (Iterative)" << endl;
        cout << "7. Linear Search" << endl;
        cout << "8. Heap Sort" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                records.Accept();
                break;
            case 2:
                records.Display();
                break;
            case 3: {
                int key;
                cout << "Enter phone number to search: ";
                cin >> key;
                int result = records.BinarySearch(key);
                if (result == -1) cout << "Record not found." << endl;
                else cout << "Record found at index " << result << "." << endl;
                break;
            }
            case 4: {
                int key;
                cout << "Enter phone number to search: ";
                cin >> key;
                int result = records.RecursiveBinarySearch(0, n - 1, key);
                if (result == -1) cout << "Record not found." << endl;
                else cout << "Record found at index " << result << "." << endl;
                break;
            }
            case 5:
                records.QuickSortRecursive(0, n - 1);
                cout << "Records sorted using Recursive Quick Sort." << endl;
                break;
            case 6:
                records.QuickSortIterative(0, n - 1);
                cout << "Records sorted using Iterative Quick Sort." << endl;
                break;
            case 7: {
                int subChoice;
                cout << "Search by:\n1. Phone Number\n2. Bill\n3. Name\nEnter choice: ";
                cin >> subChoice;
                if (subChoice == 1) {
                    int key;
                    cout << "Enter phone number: ";
                    cin >> key;
                    records.LinearSearch(1, key);
                } else if (subChoice == 2) {
                    int key;
                    cout << "Enter bill amount: ";
                    cin >> key;
                    records.LinearSearch(2, key);
                } else if (subChoice == 3) {
                    string key1;
                    cout << "Enter name: ";
                    cin >> key1;
                    records.LinearSearch(3, 0, key1);
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
            case 8:
                records.HeapSort();
                cout << "Records sorted using Heap Sort." << endl;
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
