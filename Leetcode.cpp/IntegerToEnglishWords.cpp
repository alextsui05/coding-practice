class Solution {
    static vector<string> GroupLabels;
    
public:
    string numberToWords(int num) {
        if (!num) return "Zero";
        
        stringstream ss;
        int groups[4] = {
            (num / int(1e9)) % 1000,
            (num / int(1e6)) % 1000,
            (num / int(1e3)) % 1000,
            num % 1000
        };
        for (int i = 0; i < 4; ++i) {
            if (groups[i]) {
                if (ss.str().size()) {
                    ss << ' ';
                }
                ss << toWord1000(groups[i]);
                if (GroupLabels[i].size()) {
                    ss << ' ' << GroupLabels[i];
                }
            }
        }
        return ss.str();
    }

private:
    // num in [1, 999]
    string toWord1000(int num) {
        int hundreds = num / 100;
        int remainder = num % 100;
        stringstream ss;
        if (hundreds) {
            ss << toWord20(hundreds) << " Hundred";
        }
        if (remainder) {
            if (ss.str().size())
                ss << ' ';
            ss << toWord100(remainder);
        }
        return ss.str();
    }
    
    // num in [1, 99]
    string toWord100(int num) {
        if (1 <= num && num <= 19) {
            return toWord20(num);
        }
        // num >= 20 at this point
        int tens = num / 10;
        int ones = num % 10;
        stringstream ss;
        if (tens) {
            string tensLabel;
            switch (tens) {
                case 2: tensLabel = "Twenty"; break;
                case 3: tensLabel = "Thirty"; break;
                case 4: tensLabel = "Forty"; break;
                case 5: tensLabel = "Fifty"; break;
                case 6: tensLabel = "Sixty"; break;
                case 7: tensLabel = "Seventy"; break;
                case 8: tensLabel = "Eighty"; break;
                case 9: tensLabel = "Ninety"; break;
            }
            ss << tensLabel;
        }
        if (ones) {
            if (ss.str().size())
                ss << ' ';
            ss << toWord20(ones);
        }
        return ss.str();
    }
    
    // num in [0, 19]
    string toWord20(int num) {
        switch (num) {
            case 0: return "Zero";
            case 1: return "One";
            case 2: return "Two";
            case 3: return "Three";
            case 4: return "Four";
            case 5: return "Five";
            case 6: return "Six";
            case 7: return "Seven";
            case 8: return "Eight";
            case 9: return "Nine";
            case 10: return "Ten";
            case 11: return "Eleven";
            case 12: return "Twelve";
            case 13: return "Thirteen";
            case 14: return "Fourteen";
            case 15: return "Fifteen";
            case 16: return "Sixteen";
            case 17: return "Seventeen";
            case 18: return "Eighteen";
            case 19: return "Nineteen";
        }        
    }
};

vector<string> Solution::GroupLabels {
    "Billion",
    "Million",
    "Thousand",
    ""
};