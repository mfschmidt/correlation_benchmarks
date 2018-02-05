#!/usr/bin/env bash

# Run each of the benchmark files in turn, logging output

# First, use the current date and time to generate a log file
DATE=$(date '+%Y-%m-%d-%H-%M-%S')
echo "$DATE\n\n" > benchmarks_$DATE.log

# Next, run each benchmark in turn, logging output
set -x
./naive_numpy.py | tee -a benchmarks_$DATE.log
./naive_scipy.py | tee -a benchmarks_$DATE.log
./naive_r_corr.R | tee -a benchmarks_$DATE.log

