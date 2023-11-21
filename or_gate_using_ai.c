#include <math.h>
#include <stdio.h>
#include <stdlib.h>


float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

// multiply input by 2
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

#define train_count (sizeof(train)/sizeof(train[0]))

float cost(float w1, float w2, float b) {
    float result = 0.f;
    for (size_t i = 0; i < train_count; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1 + x2*w2 + b);
        float d = y - train[i][2];
        result += d * d;
    }
    return result/train_count;
}

float rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

int main() {
    srand(0);
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();
    float eps = 1e-3;
    float rate = 1e-1;

    printf("w1: %f, w2: %f, b: %f\n", w1, w2, b);
    printf("cost: %f\n", cost(w1, w2, b));

    for(size_t i = 0; i < 5000*1000; i++) {
        float c = cost(w1, w2, b);
        float dw1 = (cost(w1 + eps, w2, b) - c) / eps;
        float dw2 = (cost(w1, w2 + eps, b) - c) / eps;
        float db = (cost(w1, w2, b + eps) - c) / eps;
        w1 -= dw1 * rate;
        w2 -= dw2 * rate;
        b -= db * rate;
        printf("w1: %f, w2: %f, b: %f, cost: %f\n", w1, w2, b, cost(w1, w2, b));
    }

    printf("w1: %f, w2: %f, b: %f\n", w1, w2, b);
    printf("cost: %f\n", cost(w1, w2, b));

    for(size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; ++j) {
            float y = sigmoidf(i * w1 + j * w2 + b);
            printf("i: %zu, j: %zu, value: %f\n", i, j, y);
        }
    }
}