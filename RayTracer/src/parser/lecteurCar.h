#ifndef __LECTEURCAR__
#define __LECTEURCAR__

#include <stdlib.h>

#include <strstream>
#include <fstream>
#include <iostream>

using namespace std;

class lecteurCar : public ifstream
{

private:
  strstream ligne;
  char *uneLigne;
  int numeroLigne;
  void lireLigne ();

public:
    lecteurCar (char nomFich[]);
   ~lecteurCar ();
  char peek ();
  void get (char &c);
  int getNumeroLigneCourante ();
  char *getLigneCourante ();


};


#endif // __LECTEURCAR__
