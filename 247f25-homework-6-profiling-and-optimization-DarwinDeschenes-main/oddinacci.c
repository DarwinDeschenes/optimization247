#include <stdlib.h>
#include "oddinacci.h"

long oddinacci(long n) {
    if (n == 0 || n == 1) {
        return n;
    } else if (n % 2 == 0) {
        return oddinacci(n - 1) + oddinacci(n - 2);
    } else {
        return oddinacci(n - 1) + oddinacci(n - 2) + oddinacci(n - 3);
    }
}

long oddinacci_fast(long n) {
    return 0;
}
