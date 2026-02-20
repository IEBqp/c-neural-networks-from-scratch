#include <stdlib.h>
#include <stdio.h>
#include "perceptron.h"

void perceptron_init(Perceptron *p, int input_count) {
    p->input_count = input_count;
    p->bias = 0.0;
    /* 
     * Since each input will have their own weight, 
     * we need a pointer to an array of doubles big enough to 
     * hold input_count amount of weights 
     * */
    p->weights = (double *) malloc(sizeof(double) * input_count);
    if (p->weights == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < input_count; i++) {
        p->weights[i] = 0.0;
    }
}

void perceptron_free(Perceptron *p) {
    free(p->weights);
    p->weights = NULL;
}

int perceptron_predict(Perceptron *p, const double *inputs) {
    /* dot(Weight vector, Input vector) + b > 0 ? true else false */
    double sum = p->bias;
    for (int i = 0; i < p->input_count; i++) {
        sum += p->weights[i] * inputs[i];
    }
    return (sum > 0) ? 1 : 0;
}
