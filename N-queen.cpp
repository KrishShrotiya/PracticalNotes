/* 
NAME: KANISHKA SHROTIYA
PRN: 1032233553
PANEL J-2
*/


#include <iostream>
using namespace std;

const int MAX_N = 10; 
int x[MAX_N]; 

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || (x[j] - i == j - k) || (i - x[j] == j - k)) {
            return false;
        }
    }
    return true;
}

void NQueen(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            x[k] = i;
            if (k == n) {
                for (int j = 1; j <= n; j++) {
                    cout << x[j] << " ";
                }
                cout << endl;
            } else {
                NQueen(k + 1, n);
            }
        }
    }
}
int main() {
    int choice, n;
    do {
        cout << "\nN-Queens Problem Menu" << endl;
        cout << "1. Solve N-Queens" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter number of queens (max " << MAX_N << "): ";
                cin >> n;
                if (n > 0 && n <= MAX_N) {
                    NQueen(1, n); 
                } else {
                    cout << "Invalid input! Please enter a value between 1 and " << MAX_N << "." << endl;
                }
                break;
            case 2:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 2);
    
    return 0;
}
