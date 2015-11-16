#include <iostream>
#include <vector>
#include <iomanip>
#include <ios>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>

using namespace std;
double invNormal(double p);
double ran2_mod(long *idum);
double gamrand(double alpha, double beta, long *idum);
void calcOptionPremium(int nSimulationPath, int nTimeStep);