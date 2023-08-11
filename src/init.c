#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP C_triangles(SEXP maximum);

static const R_CallMethodDef CallEntries[] = {
  {"C_triangles", (DL_FUNC) &C_triangles, 1},
  {NULL, NULL, 0}
};

void R_init_addr(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
