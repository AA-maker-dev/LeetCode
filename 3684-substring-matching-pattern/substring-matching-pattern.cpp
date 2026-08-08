class Solution {
public:
    bool hasMatch(string s, string p) {
        int star = p.find('*');
        string prefix = p.substr(0, star);
        string suffix = p.substr(star + 1);
        int plen = prefix.size(), slen = suffix.size();
        int n = s.size();

        if (plen == 0 && slen == 0) return true;
        if (plen == 0) return s.find(suffix) != string::npos;
        if (slen == 0) return s.find(prefix) != string::npos;

        for (int i = 0; i + plen <= n; ++i) {
            if (s.compare(i, plen, prefix) == 0) {
                for (int j = i + plen; j + slen <= n; ++j) {
                    if (s.compare(j, slen, suffix) == 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
