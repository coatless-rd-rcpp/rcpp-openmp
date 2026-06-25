# Row Euclidean Norms Computed in Parallel with OpenMP

Computes the Euclidean (L2) norm of each row of a numeric matrix, with
the rows divided across threads by *OpenMP*.

## Usage

``` r
parallel_row_norms(x)
```

## Arguments

- x:

  A `numeric` matrix.

## Value

A `numeric` vector with one entry per row of `x`, each the square root
of the sum of squares of that row.

## Details

The `#pragma omp parallel for` directive splits the outer loop over rows
across the available *OpenMP* threads. The directive is only meaningful
when the package is compiled with *OpenMP* support; without it the loop
simply runs serially.

Only the input matrix is read and the pre-allocated output vector is
written inside the parallel region, and each thread writes a distinct
index. No *R* API is touched inside the loop, which is what keeps the
routine thread-safe.

## Examples

``` r
x = matrix(rnorm(20), nrow = 5)
parallel_row_norms(x)
#> [1] 2.656382 2.013038 3.204453 1.736271 1.250746
```
