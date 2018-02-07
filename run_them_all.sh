#!/usr/bin/env bash

# Run each of the benchmark files in turn, logging output

# First, use the current date and time to generate a log file
DATE=$(date '+%Y-%m-%d-%H-%M-%S')
echo "$DATE\n\n" > benchmarks_$DATE.log

gcc naive_c.c -std=c11 -lm -o naive_c
gcc naive_c.c -std=c11 -lm -O -o ok_c
gcc naive_c.c -std=c11 -lm -O2 -o good_c
gcc naive_c.c -std=c11 -lm -O3 -o fast_c

# Next, run each benchmark in turn, logging output
set -x
echo "==-- naive_numpy.py --==" >> benchmarks_$DATE.log
./naive_numpy.py | tee -a benchmarks_$DATE.log
echo "==-- naive_scipy.py --==" >> benchmarks_$DATE.log
./naive_scipy.py | tee -a benchmarks_$DATE.log
echo "==-- naive_r_corr.R --==" >> benchmarks_$DATE.log
./naive_r_corr.R | tee -a benchmarks_$DATE.log
echo "==-- naive_c --==" >> benchmarks_$DATE.log
./naive_c | tee -a benchmarks_$DATE.log
echo "==-- ok_c --==" >> benchmarks_$DATE.log
./ok_c | tee -a benchmarks_$DATE.log
echo "==-- good_c --==" >> benchmarks_$DATE.log
./good_c | tee -a benchmarks_$DATE.log
echo "==-- fast_c --==" >> benchmarks_$DATE.log
./fast_c | tee -a benchmarks_$DATE.log

