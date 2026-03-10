/*
** main.cxx: The main routines for simulating the TAP model.
**
** Wim Hordijk   Last modified: 10 March 2026
*/

#include <iostream>
#include <string.h>
#include "TAP.h"

using namespace std;

int getArgs (int argc, char **argv);

TAP *TAPmodel;


/*
** main: The main routine of the program.
**
** Parameters:
**   - argc: The number of arguments to the program.
**   - argv: A list with the arguments.
**
** Returns:
**   - If everything went fine: 0.
**   - Otherwise:               1.
*/

int main (int argc, char **argv)
{
  int status;

  status = 0;

  /*
  ** Create a new TAP model.
  */
  TAPmodel = new TAP ();

  /*
  ** Set the model parameters.
  */
  if (getArgs (argc, argv) == -1)
  {
    status = -1;
    goto End_of_Routine;
  }

  /*
  ** Run the model.
  */
  TAPmodel->run ();
  
 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** getArgs: Get the arguments to the program.
**
** Parameters:
**   - argc: The number of arguments to the program.
**   - argv: A pointer to the list of arguments.
**
** Returns:
**   - If everything went fine:  0.
**   - Otherwise:               -1.
*/

int getArgs (int argc, char **argv)
{
  int    status, i, s, n, k, m;
  double p, a, u;

  status = 0;
  n = -1;
  m = -1;
  a = -1.0;

  /*
  ** Get and check all arguments.
  */
  i = 1;
  while (i < argc)
  {
    if (strcmp (argv[i], "-init") == 0)
    {
      if ((sscanf (argv[++i], "%d", &n) != 1) || (TAPmodel->setNrInit (n) == -1))
      {
	status = -1;
	cerr << "Invalid value for initial number of goods ('init'): " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-max") == 0)
    {
      if ((sscanf (argv[++i], "%d", &m) != 1) || (TAPmodel->setMaxM (m) == -1))
      {
	status = -1;
	cerr << "Invalid value for maximum number of goods ('max'): " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-k") == 0)
    {
      if ((sscanf (argv[++i], "%d", &k) != 1) || (TAPmodel->setK (k) == -1))
      {
	status = -1;
	cerr << "Invalid value for maximum number of parents ('K'): " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-alpha") == 0)
    {
      if ((sscanf (argv[++i], "%lg", &a) != 1) || (TAPmodel->setAlpha (a) == -1))
      {
	status = -1;
	cerr << "Invalid value for parameter 'alpha': " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-mu") == 0)
    {
      if ((sscanf (argv[++i], "%lg", &u) != 1) || (TAPmodel->setMu (u) == -1))
      {
	status = -1;
	cerr << "Invalid value for parameter 'mu': " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-seed") == 0)
    {
      if ((sscanf (argv[++i], "%d", &s) != 1) || (TAPmodel->setRndSeed (s) == -1))
      {
	status = -1;
	cerr << "Invalid value for random seed ('seed'): " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-desc") == 0)
    {
      TAPmodel->setDesc (true);
      i++;
    }
    else if (strcmp (argv[i], "-help") == 0)
    {
      cout << "Usage: " << argv[0] << " -init I -max M -alpha A [-k K] [-mu U] "
	   << "[-seed S] [-desc] [-help]" << endl << endl
	   << "  -init I:  The initial number I of goods (I>0)." << endl
	   << "  -max M:   The maximum number M of goods (when reached, the run ends)."
	   << endl
	   << "  -alpha A: The value A of the alpha parameter (0.0<=A<=1.0)." << endl
	   << "  -k K:     The maximum number K of parents (default=4)" << endl
	   << "  -mu U:    The value U of the parameter mu (default=0.0)" << endl
	   << "  -seed S:  The random seed S (default=0: use current time)." << endl
	   << "  -desc:    Generate the descent distribution." << endl
	   << "  -help:    Print this help message and exit." << endl;
      status = -1;
      goto End_of_Routine;
    }
    else
    {
      status = -1;
      cerr << "Unknow argument '" << argv[i] << "'" << endl;
      goto End_of_Routine;
    }
  }

  /*
  ** Make sure the user has set at least the 'init', 'max', and 'alpha' values.
  */
  if ((n < 0) || (m < 0) || (a < 0.0))
  {
    status = -1;
    cerr << "Expecting at least the -init, -max, and -alpha arguments..." << endl
	 << "Run '" << argv[0] << " -help' to see argument options." << endl; 
    goto End_of_Routine;
  }

 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** EoF: main.cxx
*/
