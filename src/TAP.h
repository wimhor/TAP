/*
** TAP.h: Definition of the TAP class.
**
** Wim Hordijk   Last modified: 17 September 2022
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
  int    setP       (double p);
  double getP       ();
  int    setAlpha   (double a);
  double getAlpha   ();
  int    setMu      (double u);
  double getMu      ();
  int    setPcat    (double p);
  double getPcat    ();
  void   setAnc     (bool anc);
  void   setDesc    (bool desc);
  int    run        ();
  
 private:
  /*
  ** Private member functions.
  */
  double newGoods      (double pr, int n, int k);
  void   addCatalysts  (Good *g);
  void   writeGoods    (const char *filename);
  void   writeDescDist (const char *filename);
  void   writeCRS      (const char *filename);

  /*
  ** Private member variables.
  */
  int                      rndSeed, nrGoods, nrInit, K, maxM, t;
  double                   P, alpha, mu, pCat;
  bool                     ancDAG, descDist;
  Good                    *root;
  vector<Good*>            goods, dead;
  vector<Good*>::iterator  itGood, itDead;
};


#endif  /* _TAP_H_ */

/*
** EoF: TAP.h
*/
