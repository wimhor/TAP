/*
** Good.cxx: Implementation of a good.
**
** Wim Hordijk   Last modified: 20 April 2021
*/

#include <iostream>
#include "Good.h"


/*
** Good: The constructor.
**
** Parameters:
**   - n: The good ID (some unique number).
**   - t: The time of creation of the good.
*/

Good::Good (int n, int t)
{
  /*
  ** Set variables.
  */
  ID = n;
  tBirth = t;
  tDeath = 0;
  alive = true;
}


/*
** ~Good: The destructor.
*/

Good::~Good ()
{
  /*
  ** Clear the lists.
  */
  parents.clear ();
  children.clear ();
  ancestorDAG.erase (ancestorDAG.begin (), ancestorDAG.end ());
}


/*
** getID: Get the good's ID.
**
** Returns:
**   - The ID of the good.
*/

int Good::getID ()
{
  /*
  ** Return the ID.
  */
  return (ID);
}


/*
** isAlive: Check whether the good is alive.
**
** Returns:
**   - If the good is alive: true.
**   - Otherwise:            false.
*/

bool Good::isAlive ()
{
  /*
  ** Return the status.
  */
  return (alive);
}


/*
** death: If the good is still alive, mark it as now being dead.
**
** Parameters:
**   - t: The time of death.
*/

void Good::death (int t)
{
  /*
  ** Mark the good as being dead.
  */
  if (alive)
  {
    alive = false;
    tDeath = t;
  }
}


/*
** addParent: Add a parent.
**
** Parameters:
**   - p: A pointer to the parent to add.
*/

void Good::addParent (Good *p)
{
  /*
  ** Add the parent to the list.
  */
  parents.push_back (p);
}


/*
** addChild: Add a child.
**
** Parameters:
**   - c: A pointer to the child to add.
*/

void Good::addChild (Good *c)
{
  /*
  ** Add the child to the list.
  */
  children.push_back (c);
}


/*
** addCatalyst: Add a catalyst.
**
** Parameters:
**   - c: A pointer to the catalyst to add.
*/

void Good::addCatalyst (Good *c)
{
  /*
  ** Add the catalyst to the list.
  */
  catalysts.push_back (c);
}


/*
** getNrParents: Get the number of parents.
**
** Returns:
**   - The number of parents.
*/

int Good::getNrParents ()
{
  /*
  ** Return the number of parents.
  */
  return (parents.size ());
}


/*
** getNrChildren: Get the number of children.
**
** Returns:
**   - The number of children.
*/

int Good::getNrChildren ()
{
  /*
  ** Return the number of children.
  */
  return (children.size ());
}


/*
** getNrCatalysts: Get the number of catalysts.
**
** Returns:
**   - The number of catalysts.
*/

int Good::getNrCatalysts ()
{
  /*
  ** Return the number of catalysts.
  */
  return (catalysts.size ());
}


/*
** getFirstParent: Get the first parent from the list of parents.
**
** Returns:
**   - A pointer to the first parent (or NULL if no parents).
*/

Good *Good::getFirstParent ()
{
  Good *p;

  /*
  ** Get the first parent.
  */
  itParent = parents.begin ();
  if (itParent != parents.end ())
  {
    p = *itParent;
  }
  else
  {
    p = NULL;
  }

  /*
  ** Return the result.
  */
  return (p);
}


/*
** getNextParent: Get the next parent in the list.
**
** Returns:
**   - A pointer to the next parent (or NULL if no more parents).
*/

Good *Good::getNextParent ()
{
  Good *p;

  /*
  ** Get the next parent.
  */
  itParent++;
  if (itParent != parents.end ())
  {
    p = *itParent;
  }
  else
  {
    p = NULL;
  }

  /*
  ** Return the result.
  */
  return (p);
}


/*
** getFirstChild: Get the first child from the list of children.
**
** Returns:
**   - A pointer to the first child (or NULL if no children).
*/

Good *Good::getFirstChild ()
{
  Good *c;

  /*
  ** Get the first child.
  */
  itChild = children.begin ();
  if (itChild != children.end ())
  {
    c = *itChild;
  }
  else
  {
    c = NULL;
  }

  /*
  ** Return the result.
  */
  return (c);
}


/*
** getNextChild: Get the next child in the list.
**
** Returns:
**   - A pointer to the next child (or NULL if no more children).
*/

Good *Good::getNextChild ()
{
  Good *c;

  /*
  ** Get the next child.
  */
  itChild++;
  if (itChild != children.end ())
  {
    c = *itChild;
  }
  else
  {
    c = NULL;
  }

  /*
  ** Return the result.
  */
  return (c);
}


/*
** getFirstCat: Get the first catalyst from the list of catalysts.
**
** Returns:
**   - A pointer to the first catalyst (or NULL if no catalyst).
*/

Good *Good::getFirstCat ()
{
  Good *c;

  /*
  ** Get the first catalyst.
  */
  itCat = catalysts.begin ();
  if (itCat != catalysts.end ())
  {
    c = *itCat;
  }
  else
  {
    c = NULL;
  }

  /*
  ** Return the result.
  */
  return (c);
}


/*
** getNextCat: Get the next catalyst in the list.
**
** Returns:
**   - A pointer to the next catalyst (or NULL if no more catalysts).
*/

Good *Good::getNextCat ()
{
  Good *c;

  /*
  ** Get the next catalyst.
  */
  itCat++;
  if (itCat != catalysts.end ())
  {
    c = *itCat;
  }
  else
  {
    c = NULL;
  }

  /*
  ** Return the result.
  */
  return (c);
}


/*
** getFirstDesc: Get the ID of the first descendant from the list of all descendants.
**
** Returns:
**   - The ID of the first descendant (or -1 if no descendants).
*/

int Good::getFirstDesc ()
{
  int id;

  /*
  ** Get the ID of the first descendant.
  */
  itDesc = descendants.begin ();
  if (itDesc != descendants.end ())
  {
    id = *itDesc;
  }
  else
  {
    id = -1;
  }

  /*
  ** Return the result.
  */
  return (id);
}


/*
** getNextDesc: Get the ID of the next descendant from the list of all descendants.
**
** Returns:
**   - The ID of the next descendant (or -1 if no more descendants).
*/

int Good::getNextDesc ()
{
  int id;

  /*
  ** Get the ID of the next descendant.
  */
  itDesc++;
  if (itDesc != descendants.end ())
  {
    id = *itDesc;
  }
  else
  {
    id = -1;
  }

  /*
  ** Return the result.
  */
  return (id);
}


/*
** findDesc: Recursively find all the descendants of the current good.
*/

void Good::findDesc ()
{
  int   id;
  Good *child;

  itChild = children.begin ();
  while (itChild != children.end ())
  {
    child = *itChild;
    child->findDesc ();
    id = child->getID ();
    descendants.insert (id);
    id = child->getFirstDesc ();
    while (id != -1)
    {
      descendants.insert (id);
      id = child->getNextDesc ();
    }
    itChild++;
  }
}


/*
** getNrDesc: Get the total number of descendants.
**
** Returns:
**   - The total number of descendants.
*/

int Good::getNrDesc ()
{
  return (descendants.size ());
}


/*
** genAncDAG: Generate the ancestor DAG.
*/

void Good::genAncDAG ()
{
  char                   c[8];
  string                 s;
  Good                  *p;
  list<Good*>::iterator  itP;
  set<string>            anc;
  set<string>::iterator  itAnc;
  
  /*
  ** If an initial good, use own ID. Otherwise, construct from parent DAGs.
  */
  if (tBirth == 1)
  {
    sprintf (c, "%d", ID);
    ancestorDAG.assign (c);
  }
  else
  {
    /*
    ** Get the ancestor DAGs from all parents, and temporarily store in a set, so they are
    ** automatically sorted.
    */
    itP = parents.begin ();
    while (itP != parents.end ())
    {
      p = *itP;
      p->getAncDAG (s);
      anc.insert (s);
      itP++;
    }
    /*
    ** Combine the parental ancestor DAGs into a new one.
    */
    ancestorDAG.clear ();
    ancestorDAG.append ("(");
    itAnc = anc.begin ();
    ancestorDAG.append (*itAnc);
    itAnc++;
    while (itAnc != anc.end ())
    {
      ancestorDAG.append (",");
      ancestorDAG.append (*itAnc);
      itAnc++;
    }
    ancestorDAG.append (")");
    anc.clear ();
  }
}


/*
** getAncDAG: Get a copy of the ancestor DAG.
**
** Parameters:
**  - s: A string to place the copy of the ancestor DAG in.
*/

void Good::getAncDAG (string& s)
{
  s.assign (ancestorDAG);
}


/*
** print: Write the data for the good to an output file stream.
**
** Parameters:
**   - ofs: The output file stream to write to.
*/

void Good::print (ofstream& ofs)
{
  int   id;
  Good *g;

  /*
  ** Print ID, time of birth, and time of death.
  */
  ofs << ID << " " << tBirth << " " << tDeath;
  ofs << " ";
  /*
  ** Print ID of parents.
  */
  itParent = parents.begin ();
  while (itParent != parents.end ())
  {
    g = *itParent;
    id = g->getID ();
    if (id != 0)
    {
      ofs << " " << id;
    }
    itParent++;
  }
  /*
  ** Print ancestor DAG, if present.
  */
  if ((tBirth > 1) && (ancestorDAG.length () > 0))
  {
    ofs << "  " << ancestorDAG;
  }
  ofs << endl;
}


/*
** printCRS: Write the data for the good in reaction format to an output file stream.
**
** Parameters:
**   - ofs: The output file stream to write to.
*/

void Good::printCRS (ofstream& ofs)
{
  Good *g;

  /*
  ** Print ID.
  */
  ofs << "[" << ID << "]  ";
  /*
  ** Print reaction.
  */
  itParent = parents.begin ();
  g = *itParent;
  ofs << g->getID () << " ";
  itParent++;
  while (itParent != parents.end ())
  {
    g = *itParent;
    ofs << "+ " << g->getID () << " ";
    itParent++;
  }
  ofs << "-> " << ID << "  ";
  /*
  ** Print catalysts.
  */
  ofs << "(";
  itCat = catalysts.begin ();
  if (itCat == catalysts.end ())
  {
    ofs << "_)  1";
  }
  else
  {
    g = *itCat;
    ofs << g->getID ();
    itCat++;
    while (itCat != catalysts.end ())
    {
      g = *itCat;
      ofs << " " << g->getID ();
      itCat++;
    }
    ofs << ")  1";
  }
  ofs << endl;
}


/*
** EoF: Molecule.cxx
*/
