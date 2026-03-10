# TAP
Code for numerically simulating the TAP equation. A deterministic version is implemented in an R script, while a stochastic version is implemented in C++.

This code (or extentions thereof) was used to generate the results in the following publications:
- M. Steel, W. Hordijk and S. A. Kauffman. [Dynamics of a birth-death process based on combinatorial innovation](https://www.sciencedirect.com/science/article/abs/pii/S0022519320300436). _Journal of Theoretical Biology_ 491:110187, 2020.
- W. Hordijk, S. A. Kauffman and R. Koppl. [Emergence of autocatalytic sets in a simple model of technological evolution](https://link.springer.com/article/10.1007/s00191-023-00838-2). _Journal of Evolutionary Economics_ 33:1519-1535, 2023.

The code comes without any warranty, but feel free to use it for your own purposes. If you do so, a reference to the [current repo](https://github.com/wimhor/TAP) will be appreciated.

## Compile
To compile the C++ code, go into the `src` directory and type

    make TAP

The executable will be placed in the parent directory.

## Run
To run, go back up to the parent directory and type

    ./TAP -help

to see a list of required and optional program arguments for the stochastic version. To run the deterministic version, type

    Rscript TAP.R -help

to see a list of optional script arguments (assuming R is installed on your computer).

## Arguments
The C++ program for the stochastic version requires at least some arguments, while others are optional. The R script for the deterministic version has only optional arguments. 

For the `TAP` C++ program, the following values are required:
  - `i`:    The initial number of goods (`i>0`).
  - `m`:    The maximum number of goods (when reached, the simulation ends).
  - `a`:    The parameter `alpha` (`0<=alpha<=1`).
  
while these are optional (defaults indicated):
  - `K`:    The maximum number of parents for a new good (default=`4`).
  - `u`:    The death rate (default=`0.0`).
  - `s`:    The random seed (default=`0`: will be based on current time).
  - `desc`: Generate the descent distribution.

For the `TAP.R` R script, the following values are optional (defaults indicated):
  - `a`:    The parameter `alpha` (default=`0.01`).
  - `u`:    The death rate (default=`0.0`).
  - `k`:    The maximum number of parents for a new good (default=`4`).
  - `m1`:   The initial number of goods (default=`10`).
  - `t`:    The number of time steps to simulate (default=`100`).

## Output
The C++ program will generate several output files:
  - `tap.dat`: Contains the number of goods M_t at each time step t.
  - `goods.dat`: Contains the ID number, time of birth, and time of death (`0` if not applicable) for each newly created good, together with a list of parent IDs.
  - `hist.dat`: If the `-desc` argument was included, this file contains the descent distribution as a histogram.

The R script will generate one output file:
  - `TAP.txt`: Contains the number of goods M_t at consecutive time steps.
  