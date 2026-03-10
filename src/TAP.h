/*
** TAP.h: Definition of the TAP class.
**
** Wim Hordijk   Last modified: 10 March 2026
*/

#ifndef _TAP_H_
#define _TAP_H_

#include <vector>
#include "Good.h"

using namespace std;


/*
** TAP: The TAP class.
*/

class TAP
{
 public:
  /*
  ** Constructors and destructors.
  */
   TAP  ();
  ~TAP ();

  /*
  ** Public member functions.
  */
  int    setRndSeed (int s);
  int    getRndSeed ();
  int    setNrInit  (int n);
  int    getNrInit  ();
  int    setK       (int k);
  int    getK       ();
  int    setMaxM    (int m);
  int    getMaxM    ();
  int    setAlpha   (double a);
  double getAlpha   ();
  int    setMu      (double u);
  double getMu      ();
  void   setDesc    (bool desc);
  int    run        ();
  
 private:
  /*
  ** Private member functions.
  */
  double newGoods      (double pr, int n, int k);
  void   writeGoods    (const char *filename);
  void   writeDescDist (const char *filename);

  /*
  ** Private member variables.
  */
  int                      rndSeed, nrGoods, nrInit, K, maxM, t;
  double                   alpha, mu;
  bool                     descDist;
  Good                    *root;
  vector<Good*>            goods, dead;
  vector<Good*>::iterator  itGood, itDead;
};


#endif  /* _TAP_H_ */

/*
** EoF: TAP.h
*/
