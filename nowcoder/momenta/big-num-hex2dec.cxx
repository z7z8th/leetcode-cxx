/* 
 From: https://stackoverflow.com/a/39002548
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(/* deque<unsigned> */ T &vec, bool fmthex = false) {
	if (fmthex)
		cout << hex;
	for (auto& val : vec) {
		cout << val << " ";
	}
	if (fmthex)
		cout << dec;
	cout << endl;
}

vector<unsigned short> bin2dec(vector<unsigned short> binary)
{
    vector<unsigned short> decimal;
    bool all_zero = false;

    // binary[i]: stores 8-bit of the nubmer.
    // Ex. 258 = 0x102 => binary[0] = 0x2, binary[1] = 0x1.
    while (!all_zero) {
        all_zero = true;
        for (int i = binary.size() - 1; i >= 0; i--) {
            int q = binary[i] / 10;
            int r = binary[i] % 10;

            binary[i] = q;
            if (i > 0) {
                binary[i-1] += (r << 8);
            } else {
                decimal.insert(decimal.begin(), r);
            }
            if (q != 0) {
                all_zero = false;
            }
        }
    }
    // each element stands for one digit of the decimal number.
    // Ex. 258 => decimal[0] = 2, decimal[1] = 5, decimal[2] = 8.
    return decimal; 
}

int main() {
	tuple<vector<unsigned short>, string> tcs[] {
		{ {0x99, 0x88, 0x77, 0x66}, "" },
	};
	for (auto &tc : tcs) {
		auto &bn = get<0>(tc);
		printVector(bn, true);
		auto dn = std::move(bin2dec(bn));
		printVector(dn);
	}
}