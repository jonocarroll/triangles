#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

  for (c = 1; c <= maxval; c++) {
    for (b = 1; b <= c; b++)
      for (a = 1; a <= b; a++)
        if ( ( pow ( a, 2 ) + pow ( b, 2 ) ) == pow ( c, 2 ) ) {
          triangles[a][b][c] = a + b + c;
        }
  }

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
