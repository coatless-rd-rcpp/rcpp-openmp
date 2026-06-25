#include <Rcpp.h>
#include <cmath>

#ifdef _OPENMP
#include <omp.h>
#endif

//' Row Euclidean Norms Computed in Parallel with OpenMP
//'
//' Computes the Euclidean (L2) norm of each row of a numeric matrix, with the
//' rows divided across threads by _OpenMP_.
//'
//' @param x A `numeric` matrix.
//'
//' @return
//' A `numeric` vector with one entry per row of `x`, each the square root of
//' the sum of squares of that row.
//'
//' @details
//' The `#pragma omp parallel for` directive splits the outer loop over rows
//' across the available _OpenMP_ threads. The directive is only meaningful when
//' the package is compiled with _OpenMP_ support; without it the loop simply
//' runs serially.
//'
//' Only the input matrix is read and the pre-allocated output vector is written
//' inside the parallel region, and each thread writes a distinct index. No _R_
//' API is touched inside the loop, which is what keeps the routine thread-safe.
//'
//' @examples
//' x = matrix(rnorm(20), nrow = 5)
//' parallel_row_norms(x)
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector parallel_row_norms(Rcpp::NumericMatrix x) {
  int n = x.nrow();
  int p = x.ncol();
  Rcpp::NumericVector out(n);

  #pragma omp parallel for
  for (int i = 0; i < n; i++) {
    double ss = 0.0;
    for (int j = 0; j < p; j++) {
      double v = x(i, j);
      ss += v * v;
    }
    out[i] = std::sqrt(ss);
  }

  return out;
}
