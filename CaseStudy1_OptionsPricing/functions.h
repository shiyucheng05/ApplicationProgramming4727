#include <iostream>
#include <vector>
#include <iomanip>
#include <ios>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string>

using namespace std;

void calculateOptionPrice(double userUpperBound, int userPriceStep, int userTimeStep);
pair<double, double> calcLamdas(double sigma, double nu, double theda);
double *constructExpintVector(double lamda, int step, double deltaX);
double expint(double x);
double calcSigmaSqrFcn(double lamdaP, double lamdaN, double deltaX, double nu);
double calcOmegaFcn(double lamdaP, double lamdaN, double deltaX, double nu);
pair<double, double> calculateBlBu(double sigmaSqrDeltaX, double omegaDeltaX, 
	double deltaX, double deltaTau, double riskFreeInterestRate, double dividendRate);
double populateOptionPayoff(double strikePrice, double currentXn);
double calcOptionPrice(double *omegaVector, double stepInDouble);
void triDiagSolver(double *lowerD, double *diag, double *upperD, double *B, int nSize);
void calcRMatrixAndAddToOmega(double *omegaVector, double *expintVectorLamdaN, double *expintVectorLamdaP,
	double nu, double lamdaN, double lamdaP, double* expLamdaN, double* expLamdaP, double deltaX, double deltaTau, int stepX);
