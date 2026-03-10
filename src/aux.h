/*
** aux.h: Header file for auxiliary functions.
**
** Wim Hordijk   Last modified: 7 April 2021
*/

#ifndef _AUX_H_
#define _AUX_H_

#include <stdlib.h>
#include <vector>

using namespace std;


/*
** Random numbers:
**   - UNIF01:  A uniform real value in [0.0:1.0].
**   - UNIF(n): A uniform integer value in [1:n].
**   - RNDBIT:  A random bit value (0 or 1).
*/

#define UNIF01  (double)random () / RAND_MAX
#define UNIF(n) ((random () % n) + 1)
#define RNDBIT  random () % 2


/*
** Auxiliary functions.
*/

void   rndItems (int k, int n, vector<int> *rnd);
int    Poisson  (double lambda);
int    Poisson2 (double lambda);


#endif  /* _AUX_H_ */

/*
** EoF: def.h
*/
