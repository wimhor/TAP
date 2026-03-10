/*
** Good.h: Definition of a good.
**
** Wim Hordijk   Last modified: 20 April 2021
*/

#ifndef _GOOD_H_
#define _GOOD_H_

#include <fstream>
#include <list>
#include <set>
#include <string>

using namespace std;


/*
** Good: The good class.
*/

class Good
{
 public:
  /*
  ** Constructors and destructors.
  */
  Good  (int n, int t);
  ~Good ();

  /*
  ** Public member functions.
  */
  int   getID          ();
  bool  isAlive        ();
  void  death          (int t);
  void  addParent      (Good *p);
  void  addChild       (Good *c);
  void  addCatalyst    (Good *c);
  int   getNrParents   ();
  int   getNrChildren  ();
  int   getNrCatalysts ();
  Good *getFirstParent ();
  Good *getNextParent  ();
  Good *getFirstChild  ();
  Good *getNextChild   ();
  Good *getFirstCat    ();
  Good *getNextCat     ();
  int   getFirstDesc   ();
  int   getNextDesc    ();
  void  findDesc       ();
  int   getNrDesc      ();
  void  genAncDAG      ();
  void  getAncDAG      (string& s);
  void  print          (ofstream& ofs);
  void  printCRS       (ofstream& ofs);
  
 private:
  /*
  ** Private member variables.
  */
  int                   ID, tBirth, tDeath;
  bool                  alive;
  string                ancestorDAG;
  list<Good*>           parents, children, catalysts;
  list<Good*>::iterator itParent, itChild, itCat;
  set<int>              descendants;
  set<int>::iterator    itDesc;
};


#endif  /* _GOOD_H_ */

/*
** EoF: Good.h
*/
