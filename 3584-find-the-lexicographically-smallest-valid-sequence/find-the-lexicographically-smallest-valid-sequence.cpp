#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Problem 3302: Find the Lexicographically Smallest Valid Sequence
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // last[k] stores the largest index in word1 at which word2[k] can be matched
        // such that the suffix word2[k...m-1] can be matched as an exact subsequence in word1[last[k]...n-1].
        // If word2[k...m-1] cannot be matched exactly, last[k] = -1.
        // Base case: last[m] = n (empty suffix).
        vector<int> last(m + 1, -1);
        last[m] = n;

        int p = n - 1;
        for (int k = m - 1; k >= 0; --k) {
            while (p >= 0 && word1[p] != word2[k]) {
                p--;
            }
            last[k] = p;
            if (p >= 0) {
                p--;
            }
        }

        // Store 0-indexed positions of each character in word1 for quick binary search lookup
        vector<int> pos[26];
        for (int i = 0; i < n; ++i) {
            pos[word1[i] - 'a'].push_back(i);
        }

        vector<int> seq(m);
        int prev_j = -1;
        bool changed = false;

        // Greedy matching left-to-right to construct lexicographically smallest index sequence
        for (int i = 0; i < m; ++i) {
            if (changed) {
                // If a change has already been used, all remaining characters must match word2[i] exactly.
                int char_idx = word2[i] - 'a';
                auto it = upper_bound(pos[char_idx].begin(), pos[char_idx].end(), prev_j);
                if (it == pos[char_idx].end()) {
                    return {};
                }
                int j = *it;
                seq[i] = j;
                prev_j = j;
            } else {
                // Try the smallest available index in word1, which is prev_j + 1
                int cand_j = prev_j + 1;
                if (cand_j >= n) {
                    return {};
                }

                if (word1[cand_j] == word2[i]) {
                    // Exact match at cand_j without using our single allowed change
                    seq[i] = cand_j;
                    prev_j = cand_j;
                } else {
                    // Mismatch at cand_j. Check if we can change word1[cand_j] to word2[i].
                    // This requires the remaining suffix word2[i+1...m-1] to match exactly in word1[cand_j + 1...n-1].
                    if (last[i + 1] > cand_j) {
                        seq[i] = cand_j;
                        prev_j = cand_j;
                        changed = true;
                    } else {
                        // Cannot change cand_j. Must find the first exact match for word2[i] after prev_j.
                        int char_idx = word2[i] - 'a';
                        auto it = upper_bound(pos[char_idx].begin(), pos[char_idx].end(), prev_j);
                        if (it == pos[char_idx].end()) {
                            return {};
                        }
                        int j = *it;
                        seq[i] = j;
                        prev_j = j;
                    }
                }
            }
        }

        return seq;
    }
};
