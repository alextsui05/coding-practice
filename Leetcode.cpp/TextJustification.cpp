class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        if (!words.size()) return vector<string>();
        
        vector<string> res;
        int i = 0;
        while (i < words.size()) {
            int it = i;
            int rem = maxWidth - words[it++].size();
            int len = words[i].size();
            while (it < words.size() && rem - 1 >= (int)words[it].size()) { // holy crap
                len += words[it].size();
                rem -= 1 + words[it++].size();
            }
            
            stringstream ss;
            int it_end = it;
            it = i;
            i = it_end;
            if (it_end - it == 1) { // single word case
                ss << words[it];
                if (rem)
                    ss << string(rem, ' ');
                res.push_back(ss.str());
                continue;
            }
            if (it_end == words.size()) {
                for (; it != it_end; ++it) {
                    ss << words[it];
                    if (it + 1 != it_end) {
                        ss << ' ';
                    }
                }
                rem = maxWidth - ss.str().size();
                if (rem) {
                    ss << string(rem, ' ');
                }
                res.push_back(ss.str());
                return res;
            }
            // more than one word case
            int spaces = (maxWidth - len) / (it_end - it - 1);
            int extra = (maxWidth - len) % (it_end - it - 1);
            for (; it != it_end; ++it) {
                ss << words[it];
                if (it + 1 != it_end) {
                    ss << string(spaces, ' ');
                    if (extra) {
                        ss << ' ';
                        --extra;
                    }
                }
            }
            res.push_back(ss.str());
        }
        
        return res;
    }
};
