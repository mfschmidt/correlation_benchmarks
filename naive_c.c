#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

//-----------------------------------------------------------------------------
// double pearson_correlation(double* a, double* b, int n);
// void printdata(double* independent, double* dependent, int n);


//-----------------------------------------------------------------------------
static double arithmetic_mean(double* data, int n)
{
	double total = 0;
	for(int i = 0; i < n; total += data[i], i++);
	return total / n;
}

static double mean_of_products(double* data1, double* data2, int n)
{
	double total = 0;
	for(int i = 0; i < n; total += (data1[i] * data2[i]), i++);
	return total / n;
}

static double stdev(double* data, int n)
{
	double squares[n];

	for(int i = 0; i < n; i++)
	{
		squares[i] = pow(data[i], 2);
	}

	double mean_of_squares = arithmetic_mean(squares, n);
	double mean = arithmetic_mean(data, n);
	double square_of_mean = pow(mean, 2);
	double variance = mean_of_squares - square_of_mean;

	return sqrt(variance);
}

double pearson_correlation(double* a, double* b, int n)
{
	// covariance
	double mean_of_a = arithmetic_mean(a, n);
	double mean_of_b = arithmetic_mean(b, n);
	double products_mean = mean_of_products(a, b, n);
	double covariance = products_mean - (mean_of_a * mean_of_b);

	// stdev
	double sd_of_a = stdev(a, n);
	double sd_of_b = stdev(b, n);

	// r
	return covariance / (sd_of_a * sd_of_b);
}

int text_file_to_doubles(char* filename, double* doubles, int n)
{
	double* sink = doubles;
	FILE* f = fopen(filename, "r");
	if(f == NULL) {
		printf("Could not open %s\n", filename);
		return 0;
	}
	int count = 0;
	// If n is 0, read to the end, else stop at n
	while((n == 0) || (count < n)) {
		int i = fscanf(f, "%lf", sink);
		sink++;
		if(i == 1) {
			count++;
		} else if(errno != 0) {
			perror("scanf:");
			break;
		} else if(i == EOF) {
			break;
		} else {
			printf("malformatted line %d in %s\n", count, filename);
		}
	}
	fclose(f);
	return count;
}

void printdata(double* a, double* b, int n)
{
	for(int i = 0; i < n; i++) {
		printf("%3.01f\t%3.01f\n", a[i], b[i]);
	}
}

void take_one_out(double* a, double* b, int n, double* shorts)
{
	// Allocate memory for a two duplicate arrays, and re-use them
    double new_a[n];
    double new_b[n];
    int offset = 0;
    for(int i = 0; i < n; i++) {
    	memset(new_a, 0.0, n);
    	memset(new_b, 0.0, n);
    	for(int j = 0; j < n; j++) {
        	if(i == j) {
        		offset = 1;
    	    }
	    	new_a[i] = a[i + offset];
	    	new_b[i] = b[i + offset];
    	}
    	shorts[i] = pearson_correlation(new_a, new_b, n - 1);
    }
}

void leave_one_out(double* a, double* b, int n, int i)
{

}

//-----------------------------------------------------------------------------
int main(void)
{
	double r;

	// Read the entire files in, even though we may use only a subset later
	double a[128*1024];
	int m = text_file_to_doubles(
		"/home/mike/Projects/correlation_benchmarks/vector_a.txt",
		a, 0);
	double b[128*1024];
	int n = text_file_to_doubles(
		"/home/mike/Projects/correlation_benchmarks/vector_b.txt",
		b, 0);

    if(m != n) {
		printf("Vector a (%d) and vector b (%d) are not the same length.\n", m, n);
    	return 1;
    }

    for(int i = 4; i < 8; i++) {
	    int how_many = pow(2, i) * 1024;
	    double shorts[how_many];
	    printf("  Running %d one-out correlations with c...\n", how_many);
	    clock_t begin = clock();
	    take_one_out(a, b, how_many, shorts);
	    double actual_r = pearson_correlation(a, b, how_many);
	    clock_t end = clock();
	    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	    printf("  Calculated r = %1.20lf in %1.1lf seconds.\n", actual_r, time_spent);
    }

    printf("%d values \n--------------------\n", n);
    // printdata(a, b, m);
    r = pearson_correlation(a, b, m);
    printf("Pearson correlation r = %1.20lf\n\n", r);

	return EXIT_SUCCESS;
}