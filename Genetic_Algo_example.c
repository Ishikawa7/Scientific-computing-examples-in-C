#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 100
#define MAX_GENERATIONS 100
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.7

// The fitness function we want to maximize
double f(double x) {
  return x*x;
}

// Generate a random number between min and max
double random_between(double min, double max) {
  return min + (double)rand() / ((double)RAND_MAX / (max - min));
}

// Generate a random population of individuals
double* generate_population(int size) {
  double* population = (double*)malloc(sizeof(double) * size);
  for (int i = 0; i < size; i++) {
    population[i] = random_between(-10, 10);
  }
  return population;
}

// Calculate the fitness of an individual
double calculate_fitness(double x) {
  return f(x);
}

// Select an individual using roulette wheel selection
double select_individual(double* population, double* fitnesses, int size) {
  double total_fitness = 0;
  for (int i = 0; i < size; i++) {
    total_fitness += fitnesses[i];
  }

  double point = random_between(0, total_fitness);
  double cumulative_fitness = 0;
  for (int i = 0; i < size; i++) {
    cumulative_fitness += fitnesses[i];
    if (cumulative_fitness > point) {
      return population[i];
    }
  }
  return population[size - 1];
}

// Perform crossover (recombination) between two individuals
double* crossover(double x1, double x2) {
  double* offspring = (double*)malloc(sizeof(double) * 2);
  if (random_between(0, 1) < CROSSOVER_RATE) {
    double alpha = random_between(0, 1);
    offspring[0] = alpha * x1 + (1 - alpha) * x2;
    offspring[1] = alpha * x2 + (1 - alpha) * x1;
  } else {
    offspring[0] = x1;
    offspring[1] = x2;
  }
  return offspring;
}

// Perform mutation on an individual
double mutate(double x) {
  if (random_between(0, 1) < MUTATION_RATE) {
    x = random_between(-10, 10);
  }
  return x;
}

int main() {
  srand(time(0));

  // Generate initial population
  double* population = generate_population(POPULATION_SIZE);

  // Run the genetic algorithm
    for (int i = 0; i < MAX_GENERATIONS; i++) {
        // Calculate fitness of each individual
        double* fitnesses = (double*)malloc(sizeof(double) * POPULATION_SIZE);
        for (int j = 0; j < POPULATION_SIZE; j++) {
          fitnesses[j] = calculate_fitness(population[j]);
        }
    
        // Select two parents and perform crossover
        double x1 = select_individual(population, fitnesses, POPULATION_SIZE);
        double x2 = select_individual(population, fitnesses, POPULATION_SIZE);
        double* offspring = crossover(x1, x2);
    
        // Perform mutation on the offspring
        offspring[0] = mutate(offspring[0]);
        offspring[1] = mutate(offspring[1]);
    
        // Replace the worst two individuals in the population with the offspring
        double worst_fitness = fitnesses[0];
        int worst_index = 0;
        for (int j = 1; j < POPULATION_SIZE; j++) {
          if (fitnesses[j] < worst_fitness) {
              worst_fitness = fitnesses[j];
              worst_index = j;
          }
        }
        population[worst_index] = offspring[0];
        fitnesses[worst_index] = calculate_fitness(offspring[0]);
        
        worst_fitness = fitnesses[0];
        worst_index = 0;
        for (int j = 1; j < POPULATION_SIZE; j++) {
        if (fitnesses[j] < worst_fitness) {
            worst_fitness = fitnesses[j];
            worst_index = j;
        }
        }
        population[worst_index] = offspring[1];
        fitnesses[worst_index] = calculate_fitness(offspring[1]);
    
        free(fitnesses);
        free(offspring);
    }
}
