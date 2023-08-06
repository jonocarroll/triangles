#' Calculate Pythagorean triples
#'
#' a Pythagorean triple is a set of values
#' \eqn{a}, \eqn{b}, and \eqn{c} for which \eqn{a^2 + b^2 = c^2}.
#'
#' This function calculates sets of these values such that
#' \itemize{
#'  \item{\eqn{c < maxval}}{}
#'  \item{\eqn{b <= c}}{}
#'  \item{\eqn{a <= b}}{}
#'  \item{\eqn{a^2 + b^2 = c^2}}{}
#' }
#'
#' @param maxval Maximum value of the hypotenuse. Only
#'   Pythagorean triples with `c < maxval` will be produced.
#'
#' @return a [data.frame()] consisting of the columns `a`, `b`, `c`,
#'   and `sum` where `sum = a + b + c`, the perimeter of the triangle.
#'
#' @seealso \url{https://en.wikipedia.org/wiki/Pythagorean_triple}
#'
#' @export
triangles <- function(maxval) {
  .Call("C_triangles", as.integer(maxval))
}
