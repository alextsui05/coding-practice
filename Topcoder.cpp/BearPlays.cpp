#!/usr/bin/env cppsh
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

class BearPlays {
public:

	int logMod(int k, int s) {
		int save[32];
		save[0] = 2;
		for (int i = 1; i < 32; i++) {
			long long temp = (long long)save[i - 1] * (long long)save[i - 1];
			save[i] = (temp) % s;
		}

		long long result = 1;
		for (int i = 0; i < 32; i++) {
			int temp = k >> i;
			if (temp & 0x1) {
				result = ((long long)result*(long long)save[i])%s;
			}
		}

		return result % s;
	};

	int pileSize(int A, int B, int C) {
		int S = A + B;
		int a = ((long long)A * (long long)logMod(C, S)) % S;

		return std::min(a, S - a);
	};
};

class BearPlaysSimulationApproach
{
	int next(int a, int sum) {
		return min(a + a, sum - a - a);
	}

public:
	int pileSize(int a, int b, int k) {
		if (a > b)
			swap(a, b);
		int sum = a + b;
		vector<bool> seen(1e9);
		for (int i = 0; i < k; ++i) {
			if (a == 0)
				return 0;
			if (seen[a]) {
				seen.clear();
				int len = 0;
				int it = a;
				do {
					it = next(it, sum);
					++len;
				} while (it != a);
				//cout << len << endl;

				int target = (k - i) % len;
				while (target--)
					it = next(it, sum);
				return it;
			}
			int newA = next(a, sum);
			seen[a] = true;
			a = min(newA, sum - newA);
		}

		return a;
	}
};

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " a b k" << std::endl;
        return 0;
    }
    BearPlays bp;
    int x[3] = { atoi(argv[1]),
        atoi(argv[2]),
        atoi(argv[3])
    };
    cout << bp.pileSize(x[0], x[1], x[2]) << endl;
    return 0;
}
