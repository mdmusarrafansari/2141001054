#include <stdio.h>

int main() {
    int i = 0;

    // Logical error: should be i < 5 instead of i <= 5
   // Fixed
while (i <= 5) {
    printf("i = %d\n", i);
    i++;
}

    

    return 0;
}

