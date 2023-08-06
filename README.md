
<!-- README.md is generated from README.Rmd. Please edit that file -->

# triangles

<!-- badges: start -->
<!-- badges: end -->

Wrap C code to calculate Pythagorean triples.

## Installation

You can install the development version of triangles with

``` r
# install.packages("remotes")
remotes::install_github("jonocarroll/triangles")
```

## Example

This package is purely for demonstration purposes, supporting this blog
post: <https://jcarroll.com.au/TBA>

The wrapped C code involves many features I learned about so I built
this package to support the blog post in an effort to capture as many as
possible. The processes here are not new at all, but I found many of the
existing resources to be either out of date or confusing.

The function `triangles()` takes a maximum hypotenuse length `maxval`
and produces a `data.frame()` in R. The columns represent the lengths of
the sides of a right triangle `a`, `b`, and `c` such that all of these
are integers, along with the sum of these (the perimeter of the
triangle)

``` r
library(triangles)

triangles(20)
#>   a  b  c sum
#> 1 3  4  5  12
#> 2 6  8 10  24
#> 3 5 12 13  30
#> 4 9 12 15  36
#> 5 8 15 17  40
```

This is a complete `data.frame` returned from C

``` r
x <- triangles(20)
str(x)
#> 'data.frame':    5 obs. of  4 variables:
#>  $ a  : int  3 6 5 9 8
#>  $ b  : int  4 8 12 12 15
#>  $ c  : int  5 10 13 15 17
#>  $ sum: int  12 24 30 36 40
x[x$sum > 20 & x$sum < 35, ]
#>   a  b  c sum
#> 2 6  8 10  24
#> 3 5 12 13  30
```

Various iterations of the C code can be found in [inst/src](inst/src).
