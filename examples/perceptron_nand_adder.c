#include <stdlib.h>
#include <stdio.h>
#include "perceptron.h"
#define PERCEPTRON_NAND_BIAS 3.0
#define PERCEPTRON_NAND_INPUT_SIZE 2

void perceptron_nand_init(Perceptron *p) {
    perceptron_init(p, PERCEPTRON_NAND_INPUT_SIZE);
    p->bias = PERCEPTRON_NAND_BIAS;
    p->weights[0] = p->weights[1] = -2.0;
}

int main()
{
    Perceptron perceptron_nand;
    perceptron_nand_init(&perceptron_nand);

    printf("-- Truth table for a single NAND gate made using a perceptron neuron --\n");

    printf("x1\tx2\tperceptron_nand\n");

    double inputs[2];
    double buffer[2];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inputs[0] = (double) i;
            inputs[1] = (double) j;
            printf("%d\t%d\t%d\n",i,j,perceptron_predict(&perceptron_nand, inputs));
        }
    }
    /* For a half adder made of NAND gates we need 5 NAND gates */
    Perceptron gates[5];
    for (int i = 0; i < 5; i++) {
        perceptron_nand_init(&gates[i]);
    }

    printf("-- Truth table for a half adder made of using 5 NAND gates which are made using perceptron neurons --\n");

    printf("x1\tx2\tsum\tcarry\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            /* 
             * input[0] = A
             * input[1] = B
             */

            inputs[0] = i;
            inputs[1] = j;
            int gate0 = perceptron_predict(&gates[0], inputs);

            buffer[0] = inputs[0];
            buffer[1] = gate0;
            int gate1 = perceptron_predict(&gates[1], buffer);

            buffer[0] = inputs[1];
            /* gate0 is still an input so we dont change buffer[1] here */
            int gate2 = perceptron_predict(&gates[2], buffer);

            buffer[0] = gate1;
            buffer[1] = gate2;
            int sum = perceptron_predict(&gates[3], buffer);

            buffer[0] = gate0;
            buffer[1] = gate0;
            int carry = perceptron_predict(&gates[4], buffer);

            printf("%d\t%d\t%d\t%d\n",i,j,sum,carry);
        }
    }
    perceptron_free(&perceptron_nand);
    for (int i = 0; i < 5; i++) {
        perceptron_free(&gates[i]);
    }
}
