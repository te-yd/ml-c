#ifndef _NN_H_
#define _NN_H_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define _NN_IMPLEMENTATION

#ifndef NN_ALLOC 
#define NN_ALLOC malloc
#endif

#ifndef NN_ASSERT 
#define NN_ASSERT assert
#endif

#define MAT_NON_NULL(x) NN_ASSERT(x != NULL)

#ifndef MAT
#define MAT(x) Mat_ ## x
#endif

#ifndef MATRef
#define MATRef(x) Mat *## x
#endif

#define MAT_AT(m, i, j) ((m).es[(i) * (m).cols + (j)])
#define MATRef_AT(m, i, j) ((m)->es[(i) * (m)->cols + (j)])

typedef struct {
    unsigned long rows;
    unsigned long cols;
    float *es;
} Mat;

Mat MAT(alloc)(unsigned long rows, unsigned long cols);
void MAT(dot)(Mat out, Mat in1, Mat in2);
void MAT(sum)(const Mat * const out, Mat in1, Mat in2);
void MAT(print)(Mat m);
void MAT(fill)(const Mat * const m, float value);
void MAT(randn)(const Mat * const m);
size_t MAT(size)(Mat m);

inline Mat MAT(alloc)(unsigned long rows, unsigned long cols) {
    Mat m;
    m.rows = rows;
    m.cols = cols;
    m.es = (float *) NN_ALLOC(rows * cols * sizeof(*m.es));
    return m;
}

inline void MAT(dot)(Mat out, Mat in1, Mat in2) {

}

inline void MAT(sum)(const Mat * const out, Mat in1, Mat in2) {
    MAT_NON_NULL(out);
    NN_ASSERT(in1.rows == in1.cols && in2.cols == in2.cols);
    NN_ASSERT(in1.rows == in1.cols && out->cols == out->cols);

    for (size_t i = 0; i < out->rows; i++) {
        for (size_t j = 0; j < out->cols; j++) {
            MATRef_AT(out, i, j) = MAT_AT(in1, i, j) + MAT_AT(in2, i, j);
        }
    }
}

inline void MAT(print)(Mat m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%f ", MAT_AT(m, i, j));
        }
        printf("\n");
    }
}

inline void MAT(randn)(const Mat * const m) {
    MAT_NON_NULL(m);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            MATRef_AT(m, i, j) = (float) rand() / (float) RAND_MAX;
        }
    }
}

inline void MAT(fill)(const Mat * const m, float value) {
    MAT_NON_NULL(m);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            MATRef_AT(m, i, j) = value;
        }
    }
}

inline size_t MAT(size)(Mat m) {
    return m.rows * m.cols;
}


#endif