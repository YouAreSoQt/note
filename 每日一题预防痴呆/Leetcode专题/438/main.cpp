class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sn = s.size(), pn = p.size();
        if (sn < pn) return {};
        char counter[26] = {0};
        for (int i = 0; i < pn; i++) {
            --counter[p[i] - 'a'];
            ++counter[s[i] - 'a'];
        }
        int diff = 0;
        for (auto v : counter)
            diff += (v != 0);
        vector<int> ans;
        if (diff == 0) ans.emplace_back(0);
        for (int i = pn; i < sn; i++) {
            auto oldValue = counter[s[i - pn] - 'a'];
            if (oldValue == 1) diff--;
            else if (oldValue == 0) diff++;
            counter[s[i - pn] - 'a']--;

            auto newValue = counter[s[i] - 'a'];
            if (newValue == 0) diff++;
            else if (newValue == -1) diff--;
            counter[s[i] - 'a']++;

            if (diff == 0) ans.emplace_back(i - pn + 1);
        }

        return ans;
    }
};