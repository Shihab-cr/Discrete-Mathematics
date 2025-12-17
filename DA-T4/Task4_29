#include <iostream>
using namespace std;

long long gcd_for(long long a, long long b) {
    if (a == 0 && b == 0)
        return -1; 

    if (a == 0)
        return llabs(b);

    if (b == 0)
        return llabs(a);

    long long gcd = 1;
    long long minVal = min(llabs(a), llabs(b));

    for (long long i = 1; i <= minVal; i++) {
        if (a % i == 0 && b % i == 0)
            gcd = i;
    }
    return gcd;
}

int main() {
    long long a, b;
    cin >> a >> b;

    long long result = gcd_for(a, b);

    if (result == -1)
        cout << "GCD is undefined\n";
    else
        cout << "GCD = " << result << endl;

    return 0;
}

