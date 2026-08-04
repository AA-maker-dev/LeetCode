#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int n = aliceValues.size();
        vector<pair<int, int>> stones(n);
        for (int i = 0; i < n; i++) {
            stones[i] = {aliceValues[i] + bobValues[i], i};
        }
        sort(stones.begin(), stones.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.first > b.first;
        });

        int aliceScore = 0, bobScore = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                aliceScore += aliceValues[stones[i].second];
            } else {
                bobScore += bobValues[stones[i].second];
            }
        }

        if (aliceScore > bobScore) return 1;
        if (bobScore > aliceScore) return -1;
        return 0;
    }
};