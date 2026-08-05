#include <string>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows == 1 || numRows >= n) return s;
        int T = 2 * numRows - 2;
        string result;
        result.reserve(n);
        for (int i = 0; i < numRows; i++) {
            for (int c = 0; ; c++) {
                int idx1 = c * T + i;
                if (idx1 >= n) break;
                result.push_back(s[idx1]);
                if (i == 0 || i == numRows - 1) continue;
                int idx2 = c * T + (T - i);
                if (idx2 >= n) break;
                result.push_back(s[idx2]);
            }
        }
        return result;
    }
};
