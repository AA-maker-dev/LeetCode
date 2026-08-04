//Abhi
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, INT_MIN);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int sum = 0;
            for (int k = 1; k <= 3 && i + k <= n; k++) {
                sum += stoneValue[i + k - 1];
                dp[i] = max(dp[i], sum - dp[i + k]);
            }
        }
        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};