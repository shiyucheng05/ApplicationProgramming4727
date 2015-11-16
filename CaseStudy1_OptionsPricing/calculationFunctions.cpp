// Created by Yucheng Shi ys2734

#include "functions.h"

pair<double, double> calcLamdas(double sigma, double nu, double theda)
{
	double resultOfSqrt;
	double thedaOverSigmaSquared;
	double thedaSquared = pow(theda, 2.0);
	double sigmaSquared = pow(sigma, 2.0);
	double sigmaPowerFour = pow(sigma, 4.0);

	resultOfSqrt = sqrt(thedaSquared / sigmaPowerFour + 2 / (sigmaSquared*nu));
	thedaOverSigmaSquared = theda / sigmaSquared;

	double LamdaP = resultOfSqrt - thedaOverSigmaSquared;
	double LamdaN = resultOfSqrt + thedaOverSigmaSquared;
	
	return pair<double, double>(LamdaP, LamdaN);
}

double calcSigmaSqrFcn(double lamdaP, double lamdaN, double deltaX, double nu)
{
	return (1 - (1 + lamdaP*deltaX)*exp(-lamdaP*deltaX)) / (nu*pow(lamdaP, 2.0)) + (1 - (1 + lamdaN*deltaX)*exp(-lamdaN*deltaX)) / (nu*pow(lamdaN, 2.0));
}

double calcOmegaFcn(double lamdaP, double lamdaN, double deltaX, double nu)
{
	return (expint(lamdaP*deltaX) - expint((lamdaP - 1)*deltaX)) / nu
		+(expint(lamdaN*deltaX) - expint((lamdaN + 1)*deltaX)) / nu;
}

pair<double, double> calculateBlBu(double sigmaSqrDeltaX, double omegaVectorDeltaX, double deltaX, 
	double deltaTau, double riskFreeInterestRate, double dividendRate)
{
	double partOneCalculation = 
		sigmaSqrDeltaX*deltaTau / (2 * pow(deltaX, 2.0));
	double partTwoCalculation = 
		(riskFreeInterestRate - dividendRate + omegaVectorDeltaX - 0.5 * sigmaSqrDeltaX)*deltaTau / (2 * deltaX);

	double Bl = partOneCalculation - partTwoCalculation;
	double Bu = partOneCalculation + partTwoCalculation;
	
	return pair<double, double>(Bl, Bu);
}

// populate Option payoffs in first omega column
double populateOptionPayoff(double strikePrice, double currentXn) 
{
	double differenceToStrike = strikePrice - exp(currentXn);
	if (differenceToStrike > 0) {
		return differenceToStrike;
	}
	else {
		return 0.0;
	}
}

double calcOptionPrice(double *omegaVector, double stepInDouble) 
{
	int roundedValue = (int)round(stepInDouble);
	return omegaVector[roundedValue];
}

// after the diagSolver, each time we need to calculate a R column and add it to the omega accordingly
void calcRMatrixAndAddToOmega(double *omegaVector, double *expintVectorLamdaN, double *expintVectorLamdaP,
	double nu, double lamdaN, double lamdaP, double *expLamdaN, double *expLamdaP, double deltaX, double deltaTau, int stepX)
{
	double *rVector = new double[stepX + 1]();	
	double oneOverLamdaNMultDeltaX = 1 / (lamdaN * deltaX);
	double oneOverLamdaPMultDeltaX = 1 / (lamdaP * deltaX);
	for (int rIndex = 1; rIndex <= stepX - 1; rIndex++) 
	{
		for (int kIndex1 = 1; kIndex1 <= rIndex - 1; kIndex1++) 
		{
			rVector[rIndex] = rVector[rIndex] + (omegaVector[rIndex - kIndex1] - omegaVector[rIndex] - kIndex1*(omegaVector[rIndex - kIndex1 - 1] - omegaVector[rIndex - kIndex1]))
				* (expintVectorLamdaN[kIndex1] - expintVectorLamdaN[kIndex1 + 1]) + oneOverLamdaNMultDeltaX
				* (omegaVector[rIndex - kIndex1 - 1] - omegaVector[rIndex - kIndex1]) * (expLamdaN[kIndex1] - expLamdaN[kIndex1 + 1]);
		}
		for (int kIndex2 = 1; kIndex2 <= stepX - rIndex - 1; kIndex2++) 
		{
			rVector[rIndex] = rVector[rIndex] + (omegaVector[rIndex + kIndex2] - omegaVector[rIndex] - kIndex2*(omegaVector[rIndex + kIndex2 + 1] - omegaVector[rIndex + kIndex2]))
				* (expintVectorLamdaP[kIndex2] - expintVectorLamdaP[kIndex2 + 1]) + oneOverLamdaPMultDeltaX
				* (omegaVector[rIndex + kIndex2 + 1] - omegaVector[rIndex + kIndex2]) * (expLamdaP[kIndex2] - expLamdaP[kIndex2 + 1]);
		}
	}

	// add the value of R into omega
	for (int rIndex = 1; rIndex <= stepX - 1; rIndex++)
	{
		omegaVector[rIndex] = omegaVector[rIndex] + deltaTau / nu * rVector[rIndex];
	}
	delete[] rVector;
}