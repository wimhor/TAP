/*
** TAP.cxx: Implementation of the TAP class.
**
** Wim Hordijk   Last modified: 17 September 2022
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "aux.h"
#include "TAP.h"

using namespace std;


/*
** TAP: The constructor.
*/

TAP::TAP ()
{
  /*
  ** Set default parameter values.
  */
  nrGoods = 0;
  nrInit = 0;
  maxM = 0;
  alpha = 0.01;
  K = 4;
  P = 1.0;
  mu = 0.0;
  pCat = 0.0;
  t = 1;

  /*
  ** Create an initial "virtual" good as the root (so the first real good will be in position 1).
  */
  root = new Good (0, 0);
  goods.push_back (root);

  /*
  ** Seed the random number generator (could still be overwritten by setRndSeed).
  */
  rndSeed = time (NULL);
  srandom (rndSeed);
}


/*
** ~TAP: The destructor.
*/

TAP::~TAP ()
{
  Good *g;
  
  /*
  ** Clear the allocated memory.
  */
  itGood = goods.begin ();
  while (itGood != goods.end ())
  {
    g = *itGood;
    delete g;
    itGood++;
  }
  itDead = dead.begin ();
  while (itDead != dead.end ())
  {
    g = *itDead;
    delete g;
    itDead++;
  }
  goods.clear ();
  dead.clear ();
}


/*
** setRndSeed: Set the random number seed.
**
** Parameters:
**   - s: The seed to set.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setRndSeed (int s)
{
  int status;

  status = 0;
  
  if (s < 0)
  {
    status = -1;
    goto End_of_Routine;
  }
  else if (s > 0)
  {
    rndSeed = s;
    srandom (rndSeed);
  }

 End_of_Routine:
  return (status);
}


/*
** getRndSeed: Get the random number seed.
**
** Returns:
**   The current random number seed.
*/

int TAP::getRndSeed ()
{
  return (rndSeed);
}


/*
** setNrInit: Set the initial number of goods.
**
** Parameters:
**   - n: The number of initial goods to set.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setNrInit (int n)
{
  int status;

  status = 0;
  
  if (n < 1)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    nrInit = n;
  }

 End_of_Routine:
  return (status);
}


/*
** getNrInit: Get the number of initial goods.
**
** Returns:
**   The current number of initial goods.
*/

int TAP::getNrInit ()
{
  return (nrInit);
}


/*
** setK: Set the maximum number of goods that can be combined into a new one (the parameter K).
**
** Parameters:
**   - k: The maximum number of goods to combine into a new one.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setK (int k)
{
  int status;

  status = 0;
  
  if (k < 1)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    K = k;
  }

 End_of_Routine:
  return (status);
}


/*
** getK: Get the maximum number of goods to combine (K).
**
** Returns:
**   The current maximum number of goods to combine (K).
*/

int TAP::getK ()
{
  return (K);
}


/*
** setMaxM: Set the number of goods required to reach the end of a run.
**
** Parameters:
**   - m: The number of goods required to reach the end of a run.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setMaxM (int m)
{
  int status;

  status = 0;
  
  if (m < 1)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    maxM = m;
  }

 End_of_Routine:
  return (status);
}


/*
** getMaxM: Get the number of goods required to reach the end of a run.
**
** Returns:
**   The current number of goods to reach the end of a run.
*/

int TAP::getMaxM ()
{
  return (maxM);
}


/*
** setP: Set the parameter P in the model (overall success probability).
**
** Parameters:
**   - p: The value for the parameter P in the model.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setP (double p)
{
  int status;

  status = 0;
  
  if (p < 0.0 || p > 1.0)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    P = p;
  }

 End_of_Routine:
  return (status);
}


/*
** getP: Get the value for the parameter P in the model.
**
** Returns:
**   The current value of the parameter P.
*/

double TAP::getP ()
{
  return (P);
}


/*
** setAlpha: Set the parameter alpha in the model (individual success probability).
**
** Parameters:
**   - a: The value for the parameter alpha in the model.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setAlpha (double a)
{
  int status;

  status = 0;
  
  if (a < 0.0 || a > 1.0)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    alpha = a;
  }

 End_of_Routine:
  return (status);
}


/*
** getAlpha: Get the value for the parameter alpha in the model.
**
** Returns:
**   The current value of the parameter alpha.
*/

double TAP::getAlpha ()
{
  return (alpha);
}


/*
** setMu: Set the parameter mu in the model (death rate).
**
** Parameters:
**   - u: The value for the parameter mu in the model.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setMu (double u)
{
  int status;

  status = 0;
  
  if (u < 0.0 || u > 1.0)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    mu = u;
  }

 End_of_Routine:
  return (status);
}


/*
** getMu: Get the value for the parameter mu in the model.
**
** Returns:
**   The current value of the parameter mu.
*/

double TAP::getMu ()
{
  return (mu);
}


/*
** setPcat: Set the parameter pCat (probability of catalysis) in the model.
**
** Parameters:
**   - p: The value for the parameter pCat in the model.
**
** Returns:
**   - If a valid value was provided:  0.
**   - Otherwise:                     -1.
*/

int TAP::setPcat (double p)
{
  int status;

  status = 0;
  
  if (p < 0.0 || p > 1.0)
  {
    status = -1;
    goto End_of_Routine;
  }
  else
  {
    pCat = p;
  }

 End_of_Routine:
  return (status);
}


/*
** getPcat: Get the value for the parameter pCat in the model.
**
** Returns:
**   The current value of the parameter pCat.
*/

double TAP::getPcat ()
{
  return (pCat);
}


/*
** setAnc: Set whether ancestral DAGs should be generated.
**
** Parameters:
**  - anc: Boolean indicating whether to set this option or not.
*/

void TAP::setAnc (bool anc)
{
  ancDAG = anc;
}


/*
** setDesc: Set whether the descent distribution should be generated.
**
** Parameters:
**  - desc: Boolean indicating whether to set this option or not.
*/

void TAP::setDesc (bool desc)
{
  descDist = desc;
}


/*
** run: Run the TAP model.
**
** Returns:
**   - If everyhting went fine:  0.
**   - Otherwise:               -1.
*/

int TAP::run ()
{
  int          status, i, j, k, r, nrNew;
  double       s, prob;
  char         fName[128];
  Good        *g;
  vector<int> *rnd;
  ofstream     ofile;

  status = 0;
  rnd = NULL;
  ofile.open ("tap.dat");
  
  /*
  ** Create the initial goods.
  */
  t = 1;
  for (i = 1; i <= nrInit; i++)
  {
    g = new Good (++nrGoods, t);
    g->addParent (root);
    root->addChild (g);
    if (ancDAG)
    {
      g->genAncDAG ();
    }
    goods.push_back (g);
  }
  ofile << t << " " << nrGoods << endl;
  
  /*
  ** Update the model until either the maximum number of goods or extinction is reached.
  */
  rnd = new vector<int> (K+1);
  while ((nrGoods > 0) && (nrGoods < maxM))
  {
    t++;
    /*
    ** First perform an extinction step, but never remove the initial "virtual" good.
    */
    r = Poisson (mu * nrGoods);
    if (r > nrGoods)
    {
      r = nrGoods;
    }
    for (i = 1; i <= r; i++)
    {
      k = UNIF(nrGoods);
      g = goods[k];
      g->death (t);
      dead.push_back (g);
      goods.erase (goods.begin () + k);
      nrGoods--;
    }
    /*
    ** Next, consider combinations of up to K current goods to generate new goods.
    */
    nrNew = 0;
    for (i = 1; i <= K; i++)
    {
      /*
      ** Calculate how many new goods with i parents to create.
      */
      prob = P * pow (alpha, i);
      s = newGoods (prob, nrGoods, i);
      r = Poisson (s);
      for (j = 1; j <= r; j++)
      {
	/*
	** Add a new good and assign random parents.
	*/
	nrNew++;
	g = new Good (nrGoods+nrNew, t);
	rndItems (i, nrGoods, rnd);
	for (k = 1; k <= i; k++)
	{
	  g->addParent (goods[rnd->at (k)]);
	  goods[rnd->at (k)]->addChild (g);
	}
	goods.push_back (g);
	if (ancDAG)
	{
	  g->genAncDAG ();
	}
	if (pCat > 0.0)
	{
	  addCatalysts (g);
	}
	/*
	** Stop when *exactly* maxM goods have been produced.
	** (Comment out if M_t >= maxM is used, as in the original experiments.)
	*/
	if (nrGoods + nrNew == maxM)
	{
	  i = K+1;
	  j = r+1;
	}
      }
    }
    nrGoods += nrNew;
    ofile << t << " " << nrGoods << endl;
    /*
    ** If there are new goods, write the CRS (only for growth of RAF over time analysis).
    **
    if ((nrNew > 0) && (pCat > 0.0))
    {
      sprintf (fName, "step%d.crs", t);
      writeCRS (fName);
    }
    */
  }
  ofile << endl;

  /*
  ** Save various data items, if requested.
  */
  writeGoods ("goods.dat");
  if (descDist)
  {
    writeDescDist ("hist.dat");
  }
  if (pCat > 0.0)
  {
    writeCRS ("tap.crs");
  }

 End_of_Routine:
  /*
  ** Free the allocated memory and close the file.
  */
  if (rnd != NULL)
  {
    delete rnd;
  }
  ofile.close ();

  /*
  ** Return the status.
  */
  return (status);
}


/*
** newGoods: Calculate how many new goods to expect with i parents. This assumes i is (very) small.
**
** Parameters:
**   - pr: The probability P * alpha_i.
**   - n:  The current number of goods (i.e. the number of items to choose parents from).
**   - i:  The number of parents to choose.
**
** Returns:
**   - The value pr * binom(n,i).
*/

double TAP::newGoods (double pr, int n, int i)
{
  int    j;
  double b;

  /*
  ** Calculate pr * binom(n,i).
  */
  if (i > n)
  {
    b = 0.0;
  }
  else
  {
    b = pr;
    for (j = 0; j < i; j++)
    {
      b *= ((n-j) / (j+1.0));
    }
  }

  /*
  ** Return the result.
  */
  return (b);
}


/*
** writeGoods: Write the individual goods data to file.
**
** Parameters:
**   - filename: The name of the file to write the data to.
*/

void TAP::writeGoods  (const char *filename)
{
  Good     *g;
  ofstream  ofile;

  /*
  ** Write the data to file.
  */
  ofile.open (filename);
  itGood = goods.begin ();
  itGood++;
  while (itGood != goods.end ())
  {
    g = *itGood;
    g->print (ofile);
    itGood++;
  }
  itDead = dead.begin ();
  while (itDead != dead.end ())
  {
    g = *itDead;
    g->print (ofile);
    itDead++;
  }
}


/*
** writeDescDist: Generate the descent distribution and write the histogram to file.
**
** Parameters:
**   - filename: The name of the file to write the histogram to.
*/

void TAP::writeDescDist (const char *filename)
{
  int       i, n, *hist;
  Good     *g;
  ofstream  ofile;
  
  /*
  ** Recursively generate the descendant sets for all goods.
  */
  root->findDesc ();

  /*
  ** Create the histogram of number of descendants.
  */
  hist = new int[maxM+1];
  for (i = 0; i <= maxM; i++)
  {
    hist[i] = 0;
  }
  itGood = goods.begin ();
  itGood++;
  while (itGood != goods.end ())
  {
    g = *itGood;
    n = g->getNrDesc ();
    hist[n]++;
    itGood++;
  }
  itDead = dead.begin ();
  while (itDead != dead.end ())
  {
    g = *itDead;
    n = g->getNrDesc ();
    hist[n]++;
    itDead++;
  }

  /*
  ** Write the histogram to file.
  */
  ofile.open (filename);
  for (i = 0; i <= maxM; i++)
  {
    if (hist[i] > 0)
    {
      ofile << i << " " << hist[i] << endl;
    }
  }
  ofile.close ();

  /*
  ** Free the allocated memory.
  */
  delete hist;
}


/*
** writeCRS: Write the goods data to file as a CRS (including catalysis).
**
** Note: This assumes there is no death (i.e., mu=0.0)!!
**
** Parameters:
**   - filename: The name of the file to write the data to.
*/

void TAP::writeCRS  (const char *filename)
{
  int       i;
  Good     *g;
  ofstream  ofile;

  /*
  ** Write the data to file.
  */
  ofile.open (filename);
  /*
  ** Meta data.
  */
  ofile << "<meta-data>" << endl
	<< "nrMolecules = " << nrGoods << endl
	<< "nrFoodSet   = " << nrInit << endl
	<< "nrReactions = " << nrGoods - nrInit << endl << endl;
  /*
  ** Molecules.
  */
  ofile << "<molecules>" << endl;
  for (i = 1; i <= nrGoods; i++)
  {
    ofile << "[" << i << "]  " << i << endl;
  }
  ofile << endl;
  /*
  ** Food set.
  */
  ofile << "<food set>" << endl;
  for (i = 1; i <= nrInit; i++)
  {
    ofile << "[" << i << "]  " << i << endl;
  }
  ofile << endl;
  /*
  ** Reactions.
  */
  ofile << "<reactions>" << endl;
  itGood = goods.begin ();
  itGood++;
  while (itGood != goods.end ())
  {
    g = *itGood;
    if (g->getID () > nrInit)
    {
      g->printCRS (ofile);
    }
    itGood++;
  }
}


/*
** addCatalysts: Add random catalys events for a newly created good.
**
** Parameters:
**   - g: A pointer to the new good.
*/

void TAP::addCatalysts (Good *g)
{
  Good *i;

  /*
  ** For all existing goods (i), decide with probability pCat if they will be a catalyst for the
  ** new good and/or catalyzed by the new good. Exclude the initial goods from being a catalyst or
  ** being catalyzed.
  */
  itGood = goods.begin ();
  itGood++;
  while (itGood != goods.end ())
  {
    i = *itGood;
    if (i->getID () > nrInit)
    {
      if (UNIF01 < pCat)
      {
	/*
	** Add good i as a catalyst for the new good.
	*/
	g->addCatalyst (i);
      }
      if (UNIF01 < pCat)
      {
	/*
	** Add the new good as a catalyst for good i.
	*/
	i->addCatalyst (g);
      }
    }    
    itGood++;
  }
}


/*
** EoF: TAP.cxx
*/
