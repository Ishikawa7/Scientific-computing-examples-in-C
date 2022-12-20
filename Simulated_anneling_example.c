#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// The function we want to optimize
double f(double x) {
  return x*x;
}

int main(int argc, char** argv) {
  // Set the initial temperature
  double temperature = 100.0;

  // Set the cooling rate
  double cooling_rate = 0.99;

  // Set the initial solution
  double current_solution = 5.0;

  // Set the number of iterations
  int num_iterations = 10000;

  // Set the minimum temperature
  double min_temp = 1e-10;

  for (int i = 0; i < num_iterations; i++) {
    // Generate a new solution by making a small random change to the current solution
    double new_solution = current_solution + (2.0 * rand() / RAND_MAX - 1.0);

    // Calculate the difference in cost between the new solution and the current solution
    double delta = f(new_solution) - f(current_solution);

    // If the new solution is better, accept it
    if (delta > 0) {
      current_solution = new_solution;
    }
    // If the new solution is worse, accept it with probability exp(delta / temperature)
    else {
      double probability = exp(delta / temperature);
      if (probability > (double)rand() / RAND_MAX) {
        current_solution = new_solution;
      }
    }

    // Cool the temperature
    temperature *= cooling_rate;

    // Stop the search when the temperature reaches the minimum
    if (temperature < min_temp) {
      break;
    }
  }

  printf("Best solution found: %f\n", current_solution);

  return 0;
}
