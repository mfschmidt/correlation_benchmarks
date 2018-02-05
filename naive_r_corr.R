#!/usr/bin/env Rscript

# Read in two vectors and time the performance of repeated leave-one-out correlations of them.

# Define a function to do repeated correlations
naive_r_corr <- function(a, b) {
    shorts <- c()
    for (i in 1:length(a))  {
        # Remove the pair of values at this position in the vectors
        a1 <- a[-i]
        b1 <- b[-i]
        # Recalculate the correlation without this pair and save it
        shorts[i] <- cor(a, b)
    }
}

# Get the vectors
print("Reading first vector...")
va <- scan(file="vector_a.txt")
print("Reading second vector...")
vb <- scan(file="vector_b.txt")

print("Running one-out correlations with R's cor function...")
before <- Sys.time()
short_correlations <- naive_r_corr(va, vb)
after <- Sys.time()
r <- cor(va, vb)
print(paste("Calculated r = ", format(r, nsmall=20), " in ", format(after - before, nsmall=3), sep=''))
