% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/triangles.R
\name{triangles}
\alias{triangles}
\title{Calculate Pythagorean triples}
\usage{
triangles(maxval)
}
\arguments{
\item{maxval}{Maximum value of the hypotenuse. Only
Pythagorean triples with \code{c < maxval} will be produced.}
}
\value{
a \code{\link[=data.frame]{data.frame()}} consisting of the columns \code{a}, \code{b}, \code{c},
and \code{sum} where \code{sum = a + b + c}, the perimeter of the triangle.
}
\description{
a Pythagorean triple is a set of values
\eqn{a}, \eqn{b}, and \eqn{c} for which \eqn{a^2 + b^2 = c^2}.
}
\details{
This function calculates sets of these values such that
\itemize{
\item{\eqn{c < maxval}}{}
\item{\eqn{b <= c}}{}
\item{\eqn{a <= b}}{}
\item{\eqn{a^2 + b^2 = c^2}}{}
}
}
\seealso{
\url{https://en.wikipedia.org/wiki/Pythagorean_triple}
}
