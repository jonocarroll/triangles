#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculate_sum(int maxval, int ****tri_sum) {

  int a, b, c;

  for (c = 1; c <= maxval; c++) {
    for (b = 1; b <= c; b++)
      for (a = 1; a <= b; a++)
        if ( ( pow ( a, 2 ) + pow ( b, 2 ) ) == pow ( c, 2 ) ) {
          (*tri_sum)[a][b][c] = a + b + c;
        }
  }
}

int main (int argc, char *argv[]) {

  int a, b, c;
  int maxval;
  int ***triangles;

  if ( argc != 2 ) {
    printf("Usage: triangle max_side_length\n");
    exit(EXIT_FAILURE);
  }

  maxval = atoi( argv[1] );

  triangles = (int ***) malloc (maxval * sizeof(int **));
  for (a = 0; a < maxval; ++a) {
    triangles[a] = (int **) malloc (maxval * sizeof(int *));
    for (b = 0; b < maxval; ++b) {
      triangles[a][b] = (int *) malloc (maxval * sizeof(int));
      for (c = 0; c < maxval; ++c) {
        triangles[a][b][c] = 0;
      }
    }
  }

  printf("calling external sum\n");
  calculate_sum(maxval, &triangles);

  printf("%4s\t%4s\t%4s\t%4s\n", "a", "b", "c", "sum");
  printf("   -------------------------\n");
  for (c = 1; c <= maxval; c++) {
    for (b = 1; b <= c; b++)
      for (a = 1; a <= b; a++)
        if ( ( pow ( a, 2 ) + pow ( b, 2 ) ) == pow ( c, 2 ) ) {
          printf("%4i\t%4i\t%4i\t%4i\n", a, b, c, triangles[a][b][c]);
          }
      }

  exit(EXIT_SUCCESS);

}

#include <R.h>
#include <Rinternals.h>

SEXP C_triangles(SEXP maximum) {

  int a, b, c;
  int ***triangles;

  int maxval = * INTEGER(maximum);

  triangles = (int ***) malloc (maxval * sizeof(int **));
  for (a = 0; a < maxval; ++a) {
    triangles[a] = (int **) malloc (maxval * sizeof(int *));
    for (b = 0; b < maxval; ++b) {
      triangles[a][b] = (int *) malloc (maxval * sizeof(int));
      for (c = 0; c < maxval; ++c) {
        triangles[a][b][c] = 0;
      }
    }
  }

  printf("calling C function to calc sum\n");
  calculate_sum(maxval, &triangles);

  printf("%4s\t%4s\t%4s\t%4s\n", "a", "b", "c", "sum");
  printf("   -------------------------\n");
  for (c = 1; c < maxval; ++c) {
    for (b = 1; b <= c; ++b)
      for (a = 1; a <= b; ++a)
        if ( ( pow ( a, 2 ) + pow ( b, 2 ) ) == pow ( c, 2 ) ) {
          printf("%4i\t%4i\t%4i\t%4i\n", a, b, c, triangles[a][b][c]);
        }
  }

  SEXP result = PROTECT(allocVector(LGLSXP, 1));
  LOGICAL(result)[0] = 1;
  UNPROTECT(1);

  return(result);

}
