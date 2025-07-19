#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int binomial_trial(int n, double p) {
    int success = 0;
    for (int i = 0; i < n; i++) {
        double rand_val = (double)rand() / RAND_MAX;
        if (rand_val < p) {
            success++;
        }
    }
    return success;
}

int main() {
    int n = 1000;            // TODO: Set number of trials
    double p = 0.85;         // TODO: Set probability of success
    int simulations = 1000;  // TODO: Set number of repetitions

    int i, success;
    double mean = 0.0;

    int *results = (int *)malloc(simulations * sizeof(int));

    srand(time(0));  // Seed RNG

    for (i = 0; i < simulations; i++) {
        success = binomial_trial(n,p);
        results[i] = success;
        mean += success;
    }

    mean = mean/simulations;

    // TODO: Compute standard deviation
    double std_dev = 0.0;
    for (i = 0; i < simulations; i++) {
        std_dev += pow(results[i] - mean, 2);;
    }
    std_dev = sqrt(std_dev/simulations);

    // Write to CSV
    FILE *fptr = fopen("binomial_results.csv", "w");
    fprintf(fptr, "Trial,Successes\n");
    for (i = 0; i < simulations; i++) {
        fprintf(fptr, "%d,%d\n", i + 1, results[i]);
    }
    fclose(fptr);

    printf("Mean: %.2f\n", mean);
    printf("Standard deviation: %.2f\n", std_dev);
    printf("Output saved to binomial_results.csv\n");

    free(results);
    return 0;
}

// Students complete and run this code, they will:

// Open binomial_results.csv in Python/Excel.

// Plot histogram and compare it with the Binomial PMF.

// Answer questions about how closely the simulation resembles theory.

