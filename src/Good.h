/*
** Good.h: Definition of a good.
**
** Wim Hordijk   Last modified: 10 March 2026
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
  int   getNrParents   ();
  int   getNrChildren  ();
  Good *getFirstParent ();
  Good *getNextParent  ();
  Good *getFirstChild  ();
  Good *getNextChild   ();
  int   getFirstDesc   ();
  int   getNextDesc    ();
  void  findDesc       ();
  int   getNrDesc      ();
  void  print          (ofstream& ofs);
  
 private:
  /*
  ** Private member variables.
  */
  int                   ID, tBirth, tDeath;
  bool                  alive;
  list<Good*>           parents, children;
  list<Good*>::iterator itParent, itChild;
  set<int>              descendants;
  set<int>::iterator    itDesc;
};


#endif  /* _GOOD_H_ */

/*
** EoF: Good.h
*/
