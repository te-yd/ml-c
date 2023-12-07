#include "nn.h"
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(0));
    Mat w1 = Mat_alloc(2, 2);
    Mat b1 = Mat_alloc(1, 2);

    Mat w2 = Mat_alloc(2, 1);
    Mat b2 = Mat_alloc(1, 1);

    Mat_randn(&w1);
    Mat_randn(&w2);
    Mat_randn(&b1);
    Mat_randn(&b2);

    Mat_PRINT(w1);
    Mat_PRINT(w2);
    Mat_PRINT(b1);
    Mat_PRINT(b2);

    return 0;
}