#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 10000
#define MU 100
#define SIGMA 15

// Generate a normally distributed random number using Box-Muller Transform
double generate_normal(double mean, double std_dev) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;

    double z = sqrt(-2.0 * log(u1)) * cos(2.0 * 3.14 * u2); // standard normal
    return z * std_dev + mean;
}

// PDF of normal distribution
double normal_pdf(double x, double mean, double std_dev) {
    double exponent = -((x - mean) * (x - mean)) / (2.0 * std_dev * std_dev);
    double denominator = std_dev * sqrt(2.0 * 3.14); // fixed: 92.0 was a mistake
    return exp(exponent) / denominator;
}

int main() {
    srand(time(NULL));

    FILE* fp_data = fopen("iq_scores.csv", "w");
    FILE* fp_pdf = fopen("bell_curve.csv", "w");

    if (!fp_data || !fp_pdf) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(fp_data, "IQ\n");

    int outliers = 0;

    for (int i = 0; i < N; i++) {
        double iq = generate_normal(MU, SIGMA);
        fprintf(fp_data, "%.2f\n", iq);  // fix: format specifier corrected

        if (iq <= 70 || iq >= 130) {
            outliers++;
        }
    }

    // Write bell curve data for plotting
    fprintf(fp_pdf, "x,pdf\n");
    for (double x = 40; x <= 160; x += 1.0) {
        double y = normal_pdf(x, MU, SIGMA);
        fprintf(fp_pdf, "%.2f,%.6f\n", x, y);
    }

    fclose(fp_data);
    fclose(fp_pdf);

    printf("Simulation complete.\n");
    printf("Total outliers (IQ <= 70 or IQ >= 130): %d out of %d\n", outliers, N);
    printf("Outlier percentage: %.2f%%\n", (outliers * 100.0) / N);
    printf("Data saved to 'iq_scores.csv' and 'bell_curve.csv'\n");

    return 0;
}
