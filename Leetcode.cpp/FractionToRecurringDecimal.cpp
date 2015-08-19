class Solution {
    typedef long long ll;
    
public:
    string fractionToDecimal(int numerator, int denominator) {
        stringstream ss;
        bool neg = (ll(numerator) * ll(denominator) < 0);
        ll numerato = abs(ll(numerator));
        ll denominato = abs(ll(denominator));
        if (neg)
            ss << "-";
        ss << (numerato / denominato);
        if (numerato % denominato == 0) {
            return ss.str();
        } else {
            numerato %= denominato;
        }
        
        ss << ".";
        // now have a proper fraction
        map<ll, string> divs;
        map<ll, ll> next;
        ll rem_first = numerato;
        ll repeat = 0;
        ll num = numerato;
        while (num && !repeat) {
            stringstream ss2;
            ll num_prev = num;
            num *= 10;
            // while (num < denominato) {
            //     num *= 10;
            //     ss2 << 0;
            // }
            ll div = num / denominato;
            num -= div * ll(denominato);
            ss2 << div;
            divs[num_prev] = ss2.str();
            next[num_prev] = num;
            if (next.count(num))
                repeat = num;
        }
        
        ll rem = rem_first;
        while (rem) {
            if (repeat == rem) { // build the repeated portion
                stringstream ss2;
                //ss2 << "(";
                do {
                    ss2 << divs[rem];
                    rem = next[rem];
                } while (rem != repeat);
                //ss2 << ")";
                
                // try to find ss2 in ss, otherwise append
                string str = ss.str();
                string str2 = ss2.str();
                bool found = true;
                for (int i = 0; i < str2.size(); ++i) {
                    if (str.size()-1-i < 0) {
                        found = false;
                        break;
                    }
                    if (str[str.size()-1-i] != str2[str2.size()-1-i]) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    str = str.substr(0, str.size() - str2.size());
                    str += "(";
                    str += str2;
                    str += ")";
                    return str;
                }
                
                ss << "(" << ss2.str() << ")";
                break;
            }
            
            // append next digits
            ss << divs[rem];
            rem = next[rem];
        }
        
        return ss.str();
   }
};
