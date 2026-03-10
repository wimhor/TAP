/*
** auxiliary.cxx: Auxiliary functions for the TAP program.
**
** Wim Hordijk   Last modified: 7 April 2021
*/

#include <math.h>
#include "aux.h"


/*
** rndItems: Select k random items from a list of n items.
**
** Parameters:
**   - k:   The number of random items to select.
**   - n:   The number of items to select from.
**   - rnd: A pointer to a vector (of length at least i) to put the results in.
*/

void rndItems (int k, int n, vector<int> *rnd)
{
  int          i, r, m;
  vector<int> *items;

  items = new vector<int> (n+1);
  for (i = 1; i <= n; i++)
  {
    items->at (i) = i;
  }

  for (i = 0; i < k; i++)
  {
    m = n - i;
    r = UNIF(m);
    rnd->at (i+1) = items->at (r);
    items->at (r) = items->at (m);
  }
  delete items;
}


/*
** Poisson: Draw a random number from a Poisson distribution (from Knuth).
**
** Parameters:
**   - lambda: The mean of the Poisson distribution to draw from.
**
** Returns:
**   - A random value drawn from a Poisson distribution with mean lambda.
*/

int Poisson (double lambda)
{
  int    k;
  double L, p, u;
  
  L = exp (-lambda);
  k = 0;
  p = 1.0;

  do
  {
    k++;
    u = UNIF01;
    p *= u;
  }
  while (p > L);

  return (k-1);
}


/*
** Poisson2: Draw a random number from a Poisson distribution (from Junhao, based on Knuth).
**
** Parameters:
**   - lambda: The mean of the Poisson distribution to draw from.
**
** Returns:
**   - A random value drawn from a Poisson distribution with mean lambda.
*/

int Poisson2 (double lambda)
{
  int    k, STEP;
  double p, u, lLeft;
  
  STEP = 500;
  lLeft = lambda;
  k = 0;
  p = 1.0;

  do
  {
    k++;
    u = UNIF01;
    p *= u;
    while ((p < 1) && (lLeft > 0))
    {
      if (lLeft > STEP)
      {
	p *= exp (STEP);
	lLeft -= STEP;
      }
      else
      {
	p *= exp (lLeft);
	lLeft = 0;
      }
    }
  }
  while (p > 1);

  return (k-1);
}


/*
** EoF: auxiliary.cxx
*/
