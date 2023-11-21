#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// multiply input by 2
float train[][2] = {
    {0, 3},
    {1, 5},
    {2, 7},
    {3, 9},
    {4, 11},
};

#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

float cost(float w, float b) {
    float result = 0.f;
    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * w + b;
        float d = y - train[i][1];
        result += d * d;
    }
    return result/train_count;
}

float finite_derivative(float w,  float b) {
    float eps = 1e-3;
    return (cost(w + eps, b) - cost(w, b)) / eps;
}

int main() {
    // y = Wx + B; W -> weight; B -> bias
    srand(time(0));
    float w = rand_float() * 10.0;
    float b = rand_float() * 10.0;
    float rate = 1e-3;
    float eps = 1e-3;
    printf("Model: %f %f\n", w, b);

    printf("Error: %f\n", cost(w, b));
    for (size_t i = 0; i < 25000; i++) {
        float c = cost(w, b);
        float dw = (cost(w + eps, b) - c) / eps;
        float db = (cost(w, b + eps) - c) / eps;
        w -= dw * rate;
        b -= db * rate;
        // printf("Model: %f %f\n", w, b);
    }
    printf("Error: %f\n", cost(w, b));
    printf("Model: %f %f\n", w, b);

    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * w + b;
        printf("actual: %f, expected: %f\n", y, train[i][1]);
    }
    return 0;
}