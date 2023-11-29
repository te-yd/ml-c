#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }
float rand_float() { return (float) rand() / (float) RAND_MAX; }

typedef struct {
    float or_w1;
    float or_w2;
    float or_b;
    float nand_w1;
    float nand_w2;
    float nand_b;
    float and_w1;
    float and_w2;
    float and_b;
} Xor;

Xor rand_xor() {
    Xor r = {
        .or_w1 = rand_float(),
        .or_w2 = rand_float(),
        .or_b = rand_float(),
        .nand_w1 = rand_float(),
        .nand_w2 = rand_float(),
        .nand_b = rand_float(),
        .and_w1 = rand_float(),
        .and_w2 = rand_float(),
        .and_b = rand_float()
    };
    return r;
}

void print_xor(Xor m) {
    printf("--------------------------------\n");
    printf("Model {\n");
    printf("  .or_w1: %f\n", m.or_w1);
    printf("  .or_w2: %f\n", m.or_w2);
    printf("  .or_b: %f\n", m.or_b);
    printf("  .nand_w1: %f\n", m.nand_w1);
    printf("  .nand_w2: %f\n", m.nand_w2);
    printf("  .nand_b: %f\n", m.nand_b);
    printf("  .and_w1: %f\n", m.and_w1);
    printf("  .and_w2: %f\n", m.and_w2);
    printf("  .and_b: %f\n", m.and_b);
    printf("}\n");
    printf("--------------------------------\n");
}

float forward(Xor m, float x, float y) {
    float or = sigmoidf(m.or_w1 * x + m.or_w2 * y + m.or_b);
    float and = sigmoidf(m.nand_w1 * x + m.nand_w2 * y + m.nand_b);
    float final = sigmoidf(m.and_w1 * or + m.and_w2 * and + m.and_b);
    return final;
}

size_t train_count = 4;
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

float cost(Xor m) {
    float result = 0.f;
    for (size_t i = 0; i < train_count; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(m, x1, x2);
        float d = y - train[i][2];
        result += d * d;
    }
    return result/train_count;
}

Xor step(Xor m, Xor g, float rate) {
    m.or_w1   -= rate * g.or_w1;
    m.or_w2   -= rate * g.or_w2;
    m.or_b    -= rate * g.or_b;
    m.nand_w1 -= rate * g.nand_w1;
    m.nand_w2 -= rate * g.nand_w2;
    m.nand_b  -= rate * g.nand_b;
    m.and_w1  -= rate * g.and_w1;
    m.and_w2  -= rate * g.and_w2;
    m.and_b   -= rate * g.and_b;
    return m;
}

Xor backward(Xor m, float eps) {
    Xor g;
    float c = cost(m);
    float saved;

    saved = m.or_w1;
    m.or_w1 += eps;
    g.or_w1 = (cost(m) - c) / eps;
    m.or_w1 = saved;

    saved = m.or_w2;
    m.or_w2 += eps;
    g.or_w2 = (cost(m) - c) / eps;
    m.or_w2 = saved;

    saved = m.or_b;
    m.or_b += eps;
    g.or_b = (cost(m) - c) / eps;
    m.or_b = saved;

    saved = m.nand_w1;
    m.nand_w1 += eps;
    g.nand_w1 = (cost(m) - c) / eps;
    m.nand_w1 = saved;

    saved = m.nand_w2;
    m.nand_w2 += eps;
    g.nand_w2 = (cost(m) - c) / eps;
    m.nand_w2 = saved;

    saved = m.nand_b;
    m.nand_b += eps;
    g.nand_b = (cost(m) - c) / eps;
    m.nand_b = saved;

    saved = m.and_w1;
    m.and_w1 += eps;
    g.and_w1 = (cost(m) - c) / eps;
    m.and_w1 = saved;

    saved = m.and_w2;
    m.and_w2 += eps;
    g.and_w2 = (cost(m) - c) / eps;
    m.and_w2 = saved;

    saved = m.and_b;
    m.and_b += eps;
    g.and_b = (cost(m) - c) / eps;
    m.and_b = saved;
    return g;
}


int main() {
    srand(0);

    Xor model = rand_xor();
    float eps = 1e-1;
    float rate = 1e-1;

    for (size_t i = 0; i < 500*100; ++i) {
        Xor grad = backward(model, eps);
        model = step(model, grad, rate);
        printf("cost: %f\n", cost(model));
    }

    printf("Xor Model / AND Node\n");
    for(size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            printf("%zu, %zu == %f\n", i, j, forward(model, i, j));
        }
    }

    printf("OR Node\n");
    for(size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            printf("%zu, %zu == %f\n", i, j, sigmoidf(model.or_w1 * i + model.or_w2 * j + model.or_b));
        }
    }

    printf("NAND Node\n");
    for(size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            printf("%zu, %zu == %f\n", i, j, sigmoidf(model.nand_w1 * i  + model.nand_w2 * j + model.nand_b));
        }
    }
}
