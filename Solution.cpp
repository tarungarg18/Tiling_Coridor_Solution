#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef vector<T> VT;
typedef vector<VT> VVT;

const T MOD = 1e9 + 7;

/*
Recurrence:
f(n) = 2*f(n-1) + f(n-3)

Matrix Form:

|f(n)  |   |2 0 1| |f(n-1)|
|f(n-1)| = |1 0 0| |f(n-2)|
|f(n-2)|   |0 1 0| |f(n-3)|
*/

VVT multiply(VVT& A, VVT& B) {
    int n = A.size();
    int m = A[0].size();
    int k = B[0].size();

    VVT C(n, VT(k, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            for(int l = 0; l < m; l++) {
                C[i][j] =
                (C[i][j] + A[i][l] * B[l][j]) % MOD;
            }
        }
    }

    return C;
}

VVT power(VVT& A, long long k) {

    int n = A.size();

    VVT ret(n, VT(n, 0));
    VVT B = A;

    for(int i = 0; i < n; i++)
        ret[i][i] = 1;

    while(k) {

        if(k & 1)
            ret = multiply(ret, B);

        k >>= 1;

        B = multiply(B, B);
    }

    return ret;
}

long long solve(long long n) {

    // Base cases
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(n == 2) return 2;

    // Transition Matrix
    VVT T = {
        {2, 0, 1},
        {1, 0, 0},
        {0, 1, 0}
    };

    // T^(n-2)
    VVT P = power(T, n - 2);

    /*
        Base vector:
        |f(2)|   |2|
        |f(1)| = |1|
        |f(0)|   |1|
    */

    VVT F = {
        {2},
        {1},
        {1}
    };

    // Multiply
    VVT ans = multiply(P, F);

    return ans[0][0];
}

int main() {

    long long n;
    cin >> n;

    cout << solve(n) << endl;
}
