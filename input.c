#include <stdio.h>

int main() {
    int a = 10;
    float b = 20.5;
    char c = 'z';

    if (a < 20) {
        b = a + 5;
    } else {
        b = a - 3;
    }

    while (a > 0) {
        a = a - 1;
    }

    return 0;
}
