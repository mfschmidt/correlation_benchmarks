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

for (j in 4:7) {
    n <- 2^j * 1024
    print(paste("Running", n, "one-out correlations with R's cor function..."))
    before <- Sys.time()
    short_correlations <- naive_r_corr(va[0:n], vb[0:n])
    after <- Sys.time()
    r <- cor(va[0:n], vb[0:n])
    print(paste("Calculated r = ", format(r, nsmall=20), " in ", format(after - before, nsmall=3), sep=''))
}