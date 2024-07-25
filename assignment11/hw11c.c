// name: <your name here>
// email: <your email here>

#include <stdio.h>

int d[20];

long long int dp(int n) {

    if (n>=20) {
        printf("Value of n exceeds the limit (n < 20).\n");
        return 0;
    }

    if (n == 1) return 0;
    if (n == 2) return 3;
    if (d[n] != 0) return d[n];

    d[n] = dp(n-2) * 3;
    return d[n];

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
