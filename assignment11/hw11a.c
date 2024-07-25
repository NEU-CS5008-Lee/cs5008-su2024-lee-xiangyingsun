// name: Xiangying Sun
// email: sun.xiangyi@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    if (n >= 20) {
        printf("Value of n exceeds the limit (n < 20).\n");
        return 0;
    }

    if (n == 1) return 1;
    if (n == 2) return 2;
    if (d[n] != 0) return d[n];

    d[n] = dp(n-1) + dp(n-2);
    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
