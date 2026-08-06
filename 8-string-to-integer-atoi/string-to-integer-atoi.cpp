#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;
        while (i < n && s[i] == ' ') i++;
        if (i == n) return 0;
        int sign = 1;
        if (s[i] == '+' || s[i] == '-') {
            if (s[i] == '-') sign = -1;
            i++;
        }
        int result = 0;
        bool started = false;
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';
            if (!started) {
                if (digit == 0) {
                    i++;
                    continue;
                }
                started = true;
            }
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7)) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            result = result * 10 + digit;
            i++;
        }
        if (!started) return 0;
        return sign * result;
    }
};
