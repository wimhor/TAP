#
# TAP.R: Simple R script for numerically simulating a deterministic version
#        of the TAP equation.
#
# Wim Hordijk   Last modified: 10 March 2026
#

#
# Set default parameter values.
#
# - alpha: The alpha parameter in the TAP equation. It is assumed that alpha_i = alpha^i.
# - mu:    The exitinction rate.
# - K:     The maximum number of goods to recombine (for numerical reasons).
# - M_1:   The initial number of goods.
# - T:     The number of time steps to run.
#

alpha <- 0.01
mu <- 0.0
K <- 4
M_1 <- 10
T <- 100


#
# TAP: The main function for generating a time series M_t of the number of goods
#      over time according to the TAP equation.
#
# Returns:
#   - A vector of length T containing the time series M_t.
#

TAP <- function () {
  #
  # Create an array of length T and set the first element to the initial number of goods.
  #
  m <- 1:T
  m[1] <- M_1

  #
  # Iterate the TAP equation for T-1 time steps.
  #
  for (i in 2:T) {
    s <- recombine (m[i-1])
    m[i] <- m[i-1] + s - mu*m[i-1]
  }

  #
  # Return the result.
  #
  return (m)
}


#
# recombine: The routine for calculating the number of new goods that are a result
#            of recombining currently existing goods.
#
# Parameters:
#   - n: The current number of goods.
#
# Returns:
#   - The number of new goods.
#

recombine <- function (n) {
  #
  # Recombine up to K existing goods.
  #
  s <- 0
  for (i in 1:K) {
    s <- s + ((alpha^i) * choose (n,i))
  }

  #
  # Return the result.
  #
  return (s)
}


#
# getArguments: Get the command line arguments.
#
# Parameters:
#  - args: A list of arguments.
#

getArguments <- function (args) {
  #
  # Parse the arguments.
  #
  n <- length (args)
  i <- 1
  while (i <= n) {
    if (args[i] == "-alpha") {
      alpha <<- as.numeric (args[i+1])
    } else if (args[i] == "-mu") {
      mu <<- as.numeric (args[i+1])
    } else if (args[i] == "-K") {
      K <<- as.numeric (args[i+1])
    } else if (args[i] == "-M1") {
      M_1 <<- as.numeric (args[i+1])
    } else if (args[i] == "-T") {
      T <<- as.numeric (args[i+1])
    } else if (args[i] == "-help") {
      cat ("Rscript TAP.R [-alpha <a>] [-mu <u>] [-K <k>] [-M1 <m1>] [-T <t>]\n\n")
      cat ("  - <a>:  The value of the alpha parameter (default=0.01).\n")
      cat ("  - <u>:  The value of the mu parameter (default=0.0).\n")
      cat ("  - <k>:  The maximum number of goods to recombine (default=4).\n")
      cat ("  - <m1>: The initial number of goods (default=10).\n")
      cat ("  - <t>:  The number of time steps (default=100).\n\n")
      q ("no")
    } else {
      print ("Unknown argument...")
    }
    i <- i+2
  }
}


#
# Get the arguments, iterate the equation with the given parameter values,
# and save the result in a file 'TAP.txt'.
#

args <- commandArgs (trailingOnly = TRUE)
getArguments (args)
m <- TAP()
write.table (m, file="TAP.txt", row.names=F, col.names=F)
cat ("TAP equation iterated with the following parameter values:\n")
cat ("  - alpha = ", alpha, "\n")
cat ("  - mu    = ", mu, "\n")
cat ("  - K     = ", K, "\n")
cat ("  - M_1   = ", M_1, "\n")
cat ("  - T     = ", T, "\n\n")
cat ("Results written to the file 'TAP.txt'.\n\n")
