#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int poisson_sample(double lambda) {
    double L = exp(-lambda);
    double  p =1.0;
    int k;

    for ( k = 0; k < 100; k++)
    {
        double u = (double)rand()/RAND_MAX;
        p *= u;
        if(p<=L){
            break;
        }
    }
    return k;
}


int main() {
    int hours = 168;             // One week = 7 days * 24 hours
    double lambda = 4.0;         // Average rate of calls per hour
    int calls[168];
    double sum = 0.0;


    srand(time(0));     //Initialize random seed

    //Simulate for each hour
    for (int i = 0; i < hours; i++)
    {
        calls[i] = poisson_sample(lambda);
        sum+=calls[i];
    }

    //Calculate mean
    double mean = sum/hours;

    //Calculate standard deviation
    double std_dev = 0.0;
    for (int i = 0; i < hours; i++)
    {
        std_dev += pow(calls[i]-mean,2);
    }
    std_dev = sqrt(std_dev/hours);
    
    

    // Write to CSV
    FILE *fptr = fopen("poisson_calls.csv", "w");
    fprintf(fptr, "Hour,Calls\n");
    for (int i = 0; i < hours; i++) {
        fprintf(fptr, "%d,%d\n", i + 1, calls[i]);
    }
    fclose(fptr);

    printf("Mean: %.2f\n", mean);
    printf("Standard deviation: %.2f\n", std_dev);
    printf("Output saved to poisson_calls.csv\n");

    
    return 0;
}

// Students complete and run this code, they will:

// Open binomial_results.csv in Python/Excel.

// Plot histogram and compare it with the Binomial PMF.

// Answer questions about how closely the simulation resembles theory.

