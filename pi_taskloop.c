#include <stdio.h>
#include <time.h>
#include <omp.h>
#define INTERVALS 1000000

int main(int argc, char **argv)
{
    long int i, intervals = INTERVALS;
    double x, dx, f, sum, pi;
    sum = 0.0;
    dx = 1.0 / (double) intervals;

    #pragma omp parallel shared(sum, pi) private(x, f, i) firstprivate(dx)
    {
        #pragma omp single
        {
            #pragma omp taskloop reduction(+: sum) grainsize(1000)
            for (i = 1; i <= intervals; i++) {
                x = dx * ((double) (i - 0.5));
                f = 4.0 / (1.0 + x*x);
                sum = sum + f;
            }
            pi = dx*sum;
            printf("pi = %f \n", pi);
        }
    }
    return 0;
}
