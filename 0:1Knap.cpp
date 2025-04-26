#include <iostream>

using namespace std;

int knapsack(int w[], int v[], int n, int W) {
    int dp[n + 1][W + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (w[i - 1] <= j)
                dp[i][j] = max(v[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][W];
}

int main() {
    int choice;
    do {
        cout << "\nMenu:";
        cout << "\n1. Solve Knapsack Problem";
        cout << "\n2. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int n, W;
            cout << "Enter number of items: ";
            cin >> n;
            cout << "Enter maximum weight capacity: ";
            cin >> W;
            int w[n], v[n];
            cout << "Enter weight and value of each item:\n";
            for (int i = 0; i < n; i++)
                cin >> w[i] >> v[i];
            cout << "Maximum value that can be obtained: " << knapsack(w, v, n, W) << "\n";
        }
    } while (choice != 2);
    return 0;
}