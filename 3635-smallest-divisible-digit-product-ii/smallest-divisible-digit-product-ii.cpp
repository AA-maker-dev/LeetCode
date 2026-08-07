#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long temp_t = t;
        int a2 = 0, a3 = 0, a5 = 0, a7 = 0;
        while (temp_t % 2 == 0) { a2++; temp_t /= 2; }
        while (temp_t % 3 == 0) { a3++; temp_t /= 3; }
        while (temp_t % 5 == 0) { a5++; temp_t /= 5; }
        while (temp_t % 7 == 0) { a7++; temp_t /= 7; }

        if (temp_t > 1) return "-1";

        int factors[10][4] = {
            {0, 0, 0, 0}, // 0
            {0, 0, 0, 0}, // 1
            {1, 0, 0, 0}, // 2
            {0, 1, 0, 0}, // 3
            {2, 0, 0, 0}, // 4
            {0, 0, 1, 0}, // 5
            {1, 1, 0, 0}, // 6
            {0, 0, 0, 1}, // 7
            {3, 0, 0, 0}, // 8
            {0, 2, 0, 0}  // 9
        };

        auto get_min_suffix = [&](int r2, int r3, int r5, int r7) -> string {
            r2 = max(0, r2);
            r3 = max(0, r3);
            r5 = max(0, r5);
            r7 = max(0, r7);

            string best_str = "";
            bool has_best = false;

            for (int c6 = 0; c6 < 6; ++c6) {
                int rem2 = max(0, r2 - c6);
                int rem3 = max(0, r3 - c6);

                int c8 = rem2 / 3;
                int rem2_mod = rem2 % 3;
                int c4 = (rem2_mod == 2) ? 1 : 0;
                int c2 = (rem2_mod == 1) ? 1 : 0;

                int c9 = rem3 / 2;
                int rem3_mod = rem3 % 2;
                int c3 = (rem3_mod == 1) ? 1 : 0;

                int c5 = r5;
                int c7 = r7;

                string cand = "";
                cand.append(c2, '2');
                cand.append(c3, '3');
                cand.append(c4, '4');
                cand.append(c5, '5');
                cand.append(c6, '6');
                cand.append(c7, '7');
                cand.append(c8, '8');
                cand.append(c9, '9');

                if (!has_best) {
                    best_str = cand;
                    has_best = true;
                } else {
                    if (cand.length() < best_str.length() || 
                       (cand.length() == best_str.length() && cand < best_str)) {
                        best_str = cand;
                    }
                }
            }
            return best_str;
        };

        int N = num.length();
        int first_zero_idx = N;
        for (int i = 0; i < N; ++i) {
            if (num[i] == '0') {
                first_zero_idx = i;
                break;
            }
        }

        struct FactorCount { int f2, f3, f5, f7; };
        vector<FactorCount> prefix_factors(N + 1, {0, 0, 0, 0});
        int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
        for (int idx = 0; idx < N; ++idx) {
            int d = num[idx] - '0';
            p2 += factors[d][0];
            p3 += factors[d][1];
            p5 += factors[d][2];
            p7 += factors[d][3];
            prefix_factors[idx + 1] = {p2, p3, p5, p7};
        }

        // Case 1: num itself
        if (first_zero_idx == N) {
            auto pf = prefix_factors[N];
            if (pf.f2 >= a2 && pf.f3 >= a3 && pf.f5 >= a5 && pf.f7 >= a7) {
                return num;
            }
        }

        // Case 2: Matching prefix up to i
        for (int i = min(N - 1, first_zero_idx); i >= 0; --i) {
            auto pf = prefix_factors[i];
            int cur_digit = num[i] - '0';

            for (int d = cur_digit + 1; d <= 9; ++d) {
                int rem2 = a2 - (pf.f2 + factors[d][0]);
                int rem3 = a3 - (pf.f3 + factors[d][1]);
                int rem5 = a5 - (pf.f5 + factors[d][2]);
                int rem7 = a7 - (pf.f7 + factors[d][3]);

                string suffix_str = get_min_suffix(rem2, rem3, rem5, rem7);
                int rem_len = N - 1 - i;

                if ((int)suffix_str.length() <= rem_len) {
                    int ones_count = rem_len - suffix_str.length();
                    string res = num.substr(0, i);
                    res += (char)('0' + d);
                    res.append(ones_count, '1');
                    res += suffix_str;
                    return res;
                }
            }
        }

        // Case 3: Length > N
        string full_suffix = get_min_suffix(a2, a3, a5, a7);
        int target_len = max(N + 1, (int)full_suffix.length());
        int ones_count = target_len - full_suffix.length();
        string res = "";
        res.append(ones_count, '1');
        res += full_suffix;
        return res;
    }
};
