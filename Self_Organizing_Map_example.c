#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Implementation of a 1D self-organizing map (SOM) in C

// Set the dimensions of the SOM
#define NUM_INPUTS 2  // Number of input features (2D data)
#define NUM_NEURONS 3  // Number of neurons in the SOM

// Set the learning rate and number of iterations
#define LEARNING_RATE 0.1
#define NUM_ITERATIONS 1000

int main()
{
    // Initialize the weights of the SOM randomly using a Gaussian distribution
    double weights[NUM_NEURONS][NUM_INPUTS];
    for (int i = 0; i < NUM_NEURONS; i++) {
        for (int j = 0; j < NUM_INPUTS; j++) {
            weights[i][j] = rand() / (double)RAND_MAX;
        }
    }

    // Loop over the number of iterations
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        // Select a random input data point
        double input_data[NUM_INPUTS];
        for (int i = 0; i < NUM_INPUTS; i++) {
            input_data[i] = rand() / (double)RAND_MAX;
        }

        // Compute the distances between the input data and the weights of the SOM
        double distances[NUM_NEURONS];
        for (int i = 0; i < NUM_NEURONS; i++) {
            double sum = 0;
            for (int j = 0; j < NUM_INPUTS; j++) {
                sum += (input_data[j] - weights[i][j]) * (input_data[j] - weights[i][j]);
            }
            distances[i] = sqrt(sum);
        }

        // Find the winning neuron (i.e., the one with the smallest distance)
        int winning_neuron = 0;
        for (int i = 1; i < NUM_NEURONS; i++) {
            if (distances[i] < distances[winning_neuron]) {
                winning_neuron = i;
            }
        }

        // Update the weights of the winning neuron and its neighbors
        for (int i = 0; i < NUM_INPUTS; i++) {
            weights[winning_neuron][i] += LEARNING_RATE * (input_data[i] - weights[winning_neuron][i]);
        }
        if (winning_neuron > 0) {
            for (int i = 0; i < NUM_INPUTS; i++) {
                weights[winning_neuron - 1][i] += LEARNING_RATE * (input_data[i] - weights[winning_neuron - 1][i]);
            }
        }
        if (winning_neuron < NUM_NEURONS - 1) {
            for (int i = 0; i < NUM_INPUTS; i++) {
                weights[winning_neuron + 1][i] += LEARNING_RATE * (input_data[i] - weights[winning_neuron + 1][i]);
            }
        }
    }
    // Print the weights of the SOM
    for (int i = 0; i < NUM_NEURONS; i++) {
        for (int j = 0; j < NUM_INPUTS; j++) {
            printf("%f ", weights[i][j]);
        }
        printf("/n");
    }
    printf("/n");
}