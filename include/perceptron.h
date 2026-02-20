#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct {
    double *weights;
    double bias;
    int input_count;
} Perceptron;

void perceptron_init(Perceptron *p, int input_count);
int perceptron_predict(Perceptron *p, const double *inputs);
void perceptron_free(Perceptron *p);

#endif
