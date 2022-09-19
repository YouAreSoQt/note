class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int p = s.size() - 1, q = t.size() - 1;
        while (p >= 0 || q >= 0) {
            int skipS = 0;
            while (p >= 0 && (s[p] == '#' || skipS > 0)) {
                skipS += s[p] == '#' ? 1 : -1;
                p--;
            }
            int skipT = 0;
            while (q >= 0 && (t[q] == '#' || skipT > 0)) {
                skipT += t[q] == '#' ? 1 : -1;
                q--;
            }
            if (p >= 0 && q >= 0) {
                if (s[p] != t[q]) {
                    return false;
                }
            } else if (p >= 0 || q >= 0) {
                return false;
            }
            p--;
            q--;
        }
        return true;
    }
};