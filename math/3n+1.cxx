#include <iostream>
#include <bitset>

using namespace std;

unsigned int my_fls(unsigned n)
{
    return 31 - __builtin_clz(n|1);
}

inline void prb(unsigned n)
{
    // cout << n << "(" << bitset<32>(n) << ") ";
    cout << hex << n << " ";
}

bitset<__UINT32_MAX__> valcc;
int cc_hitcnt = 0;
unsigned max_val = 0;
int max_bitset = 0;
unsigned max_bitset_n = 0;

unsigned tnp1(unsigned n)
{
    unsigned orig_n = n;
    valcc.set(n, true);

    int iter=0;
    int this_max_bitset = my_fls(n);
    do {
        ++iter;
        prb(n);

        if (n&1) {
            if (n&(3<<30)) {
                cout << "error 32 bit int overflow" << endl;
                exit(-1);
            }
            n = (n<<1)+n+1;
        } else {
            n = n>>1;
        }
        int ls = my_fls(n);
        if (ls > this_max_bitset) {
            this_max_bitset = ls;
        }
        if (n > max_val)
            max_val = n;
        if (valcc.test(n)) {
            ++cc_hitcnt;
            prb(n);
            cout << "(HIT)";
            break;
        }
    } while (n >= 2);

    cout << "(iter " << dec << iter << ")(maxbit " << this_max_bitset << ")" <<endl<<endl;
    if (this_max_bitset > max_bitset) {
        max_bitset = this_max_bitset;
        max_bitset_n = orig_n;
    }

    return iter;
}




int main(int argc, char *argv[])
{
    int max_iter = 0;
    for (unsigned i=0; i < 1<<8; i++)  // 1<<16
    {
        int iter = tnp1(i);
        if (iter > max_iter)
            max_iter = iter;
    }

    cout << dec;

    cout << "__UINT32_MAX__ " << __UINT32_MAX__ << endl;
    cout << "cc size " << valcc.size() << endl;
    cout << "max iter " << max_iter << endl;
    cout << "max val " << max_val << endl;
    cout << "max bitset " << max_bitset << " of n " << max_bitset_n << "(0x" << hex << max_bitset_n << ")" << dec << endl;
    cout << "cc hitcnt " << cc_hitcnt << endl;

    int wait;
    cin >> wait;
    
    return 0;
}