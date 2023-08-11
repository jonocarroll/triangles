#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculate_sum(int maxval, int ****tri_sum) {

  int a, b, c;

  for (c = 1; c < maxval; c++) {
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

  calculate_sum(maxval, &triangles);

  /* count rows */
  int nrows = 0;
  for (c = 1; c < maxval; ++c) {
    for (b = 1; b <= c; ++b)
      for (a = 1; a <= b; ++a)
        if (triangles[a][b][c] != 0) {
          nrows += 1;
        }
  }

  /* output a data.frame */
  int ncols = 4;

  SEXP col1, col2, col3, col4, df;
  PROTECT(df = allocVector(VECSXP, ncols));

  PROTECT(col1 = allocVector(INTSXP, nrows));
  PROTECT(col2 = allocVector(INTSXP, nrows));
  PROTECT(col3 = allocVector(INTSXP, nrows));
  PROTECT(col4 = allocVector(INTSXP, nrows));

  int j = 0;
  for (c = 1; c < maxval; ++c) {
    for (b = 1; b <= c; ++b) {
      for (a = 1; a <= b; ++a) {
        if (triangles[a][b][c] != 0) {
          INTEGER(col1)[j] = a;
          INTEGER(col2)[j] = b;
          INTEGER(col3)[j] = c;
          INTEGER(col4)[j] = triangles[a][b][c];
          j += 1;
        }
      }
    }
  }

  SET_VECTOR_ELT(df, 0, col1);
  SET_VECTOR_ELT(df, 1, col2);
  SET_VECTOR_ELT(df, 2, col3);
  SET_VECTOR_ELT(df, 3, col4);

  SEXP colNames;
  PROTECT(colNames = allocVector(STRSXP, ncols));
  SET_STRING_ELT(colNames, 0, mkChar("a"));
  SET_STRING_ELT(colNames, 1, mkChar("b"));
  SET_STRING_ELT(colNames, 2, mkChar("c"));
  SET_STRING_ELT(colNames, 3, mkChar("sum"));
  setAttrib(df, R_NamesSymbol, colNames);

  SEXP rowNames;
  PROTECT(rowNames = allocVector(STRSXP, nrows));
  for (int i = 0; i < nrows; ++i) {
    char rowName[10];
    snprintf(rowName, sizeof(rowName), "%d", i + 1);
    SET_STRING_ELT(rowNames, i, mkChar(rowName));
  }
  setAttrib(df, R_RowNamesSymbol, rowNames);

  SEXP className;
  PROTECT(className = allocVector(STRSXP, 1));
  SET_STRING_ELT(className, 0, mkChar("data.frame"));
  classgets(df, className);

  UNPROTECT(8);
  return df;

}
