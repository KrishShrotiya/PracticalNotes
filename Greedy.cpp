/* 
NAME: KANISHKA SHROTIYA
PRN: 1032233553
PANEL J-2

LEETCODE - 322 Unbounded Knapsack problem
*/

#include <vector>
using namespace std;

class Solution {
    public:  
        int coinChange(vector<int> &coinValues, int targetAmount) {  
            int unreachable = 1000000;  
            vector<int> minCoins(targetAmount + 1, unreachable);  
            minCoins[0] = 0;  

            for (int currentAmount = 1; currentAmount <= targetAmount; currentAmount++) {  
                for (int i = 0; i < coinValues.size(); i++) {  
                    if (currentAmount >= coinValues[i] && minCoins[currentAmount - coinValues[i]] != unreachable) {  
                        minCoins[currentAmount] = min(minCoins[currentAmount], 1 + minCoins[currentAmount - coinValues[i]]);  
                    }  
                }  
            }  

            if (minCoins[targetAmount] == unreachable) {  
                return -1;  
            }  
            return minCoins[targetAmount];  
        }  
};


