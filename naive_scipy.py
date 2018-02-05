#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Feb  2 20:24:31 2018

@author: mike

Use the scipy pearsonr function to brute force the Pearson correlation
between two vectors, each in a csv file.
"""

# Imports
import sys
import os
my_path = os.path.abspath(os.path.dirname(__file__))
sys.path.insert(0, my_path)

import numpy as np
from scipy.stats import pearsonr
import timeit

# Define the function we need to do all the partial correlations.
def naive_scipy_correlations(a, b):
    """ Repeatedly recalculate the correlation from scratch
    after removing each item from the arrays.
    """
    short_correlations = np.zeros(len(a))
    for i in range(len(a)):
        a1 = np.delete(a, i)
        b1 = np.delete(b, i)
        short_correlations[i] = pearsonr(a1, b1)[0]
    return short_correlations

# Get the test data sets and run them.
print("Reading first vector...")
va = np.genfromtxt(os.path.join(my_path, "vector_a.txt"))
print("Reading second vector...")
vb = np.genfromtxt(os.path.join(my_path, "vector_b.txt"))

# Run correlations with numpy and report them
for i in range(4,8):
    n = 2**i * 1024
    print("  Running {} one-out correlations with scipy...".format(n))
    seconds = timeit.timeit(stmt='shorts = naive_scipy_correlations(va[:n], vb[:n])', number=1, globals=globals())
    actual_r = pearsonr(va[:n], vb[:n])[0]
    print("  Calculated r = {r:0.20f} in {t:0.3f} seconds.".format(r=actual_r, t=seconds))
