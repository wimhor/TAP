#
# TAP.R: R functions for running a deterministic ("expectation-based") version
#        of the TAP model.
#
# Wim Hordijk   Last modified: 19 July 2019
#

#
# M: The main function for calculating a time series M_t of the number of goods over time.
#
# Parameters:
#   - m_1: The initial number of goods.
#   - t:   The number of time steps to calculate M_t for.
#
# Returns:
#   - A vector of length t containing the time series M_t.
#

M <- function (m_1, t) {
  m <- 1:t
  m[1] <- m_1

  for (i in 2:t) {
    s <- tinker (m[i-1])
    m[i] <- m[i-1] + s
  }
  
  return (m)
}


#
# tinker: The routine for calculating the number of new goods that are a result
#         of "tinkering" with subsets of n current goods (the sum part in the model).
#
# Parameters:
#   - n: The current number of goods.
#
# Returns:
#   - The number of new goods.
#

tinker <- function (n) {
  a <- 0.01
  p <- 1.0
  s <- 0
  k <- n

  if (k > 4) {
    k <- 4
  }
  for (i in 1:k) {
    s <- s + ((a^i) * choose (n,i))
  }

  return (p*s)
}


#
# E_T: Calculate the expected time E[T] to explosion in the TAP model.
#
# Parameters:
#   - a:   The value of a in the model.
#   - M_1: The value of M_1 in the model.
#   - P:   The value of P in the model.
#   - n:   The number of elements to sum over.
#
# Returns:
#   - An approximation of E[T].
#

E_T <- function (a, M_1, P, n) {
  E <- 0
  x <- 1 + a
  k <- M_1 - 1

  for (i in 1:n) {
    E <- E + ((x^(-i*k)) / ((x^i) - 1))
  }
  E <- E / P

  return (E)
}


#
# Var_T: Calculate the variance of the time T to explosion in the TAP model.
#
# Parameters:
#   - a:   The value of a in the model.
#   - M_1: The value of M_1 in the model.
#   - P:   The value of P in the model.
#   - n:   The number of elements to sum over (n>k).
#
# Returns:
#   - An approximation of Var[T].
#

Var_T <- function (a, M_1, P, n) {
  V <- 0
  x <- 1 + a
  k <- M_1 - 1

  for (i in 2:n) {
    V <- V + ((x^(-i*k)) / ((x^i) - 1))
  }
  V <- V / (P^2)

  return (V)
}


#
# Run the model with M_1=10 and T=251.
#

det <- M(10,251)
E_T(0.01,10,1.0,200)
v<-Var_T(0.01,10,1.0,200)
2*sqrt(v)
