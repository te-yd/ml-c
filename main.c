#include "nn.h"
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(0));
    Mat m1 = Mat_alloc(2, 2);
    Mat m2 = Mat_alloc(12, 12);

    Mat_fill(&m1, 1);
    Mat_fill(&m2, 3);

    Mat_sum(&m1, m1, m2);
    Mat_print(m1);
}