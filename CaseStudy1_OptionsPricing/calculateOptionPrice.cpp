// Created by Yucheng Shi ys2734

#include "functions.h"

void calculateOptionPrice(double userUpperBound, int userPriceStep, int userTimeStep)
{
	// define data set
	double sigma = 0.2;
	double nu = 0.14;
	double theda = -0.13;
	double riskFreeInterestRate = 0.25 / 100;
	double dividendRate = 1.5 / 100;
	double maturityLength = 0.25;

	double lowerBoundX = log(1600);
	double strikePrice = 1800;

	// user could customize upperbound
	double upperBoundX = log(userUpperBound);
	double spotPrice = 1975;

	// according to step of x and tau, defines delta X and delta Tau
	int stepX = userPriceStep;
	int stepTime = userTimeStep;
	double deltaX = (upperBoundX - lowerBoundX) / stepX;
	double deltaTau = maturityLength / stepTime;

	// start the clock to count the execution time
	clock_t start, end;
	start = clock();

	// this will return a pair of value lamdaN and lamdaP
	pair<double, double> lamdaPair = calcLamdas(sigma, nu, theda);
	double lamdaP = lamdaPair.first;
	double lamdaN = lamdaPair.second;

	// pre-populate all values that require expint calculation
	double *expintVectorLamdaN = constructExpintVector(lamdaN, stepX, deltaX);
	double *expintVectorLamdaP = constructExpintVector(lamdaP, stepX, deltaX);

	// pre-populate all values that require exp calculation
	double *expLamdaN = new double[stepX + 1]();
	double *expLamdaP = new double[stepX + 1]();
	for (int index = 0; index <= stepX; index++)
	{
		expLamdaN[index] = exp(-lamdaN*index*deltaX);
		expLamdaP[index] = exp(-lamdaP*index*deltaX);
	}

	// calculate sigmaSuaredDeltaX and omegaDeltaX
	double sigmaSqrDeltaX = calcSigmaSqrFcn(lamdaP, lamdaN, deltaX, nu);
	double omegaDeltaX = calcOmegaFcn(lamdaP, lamdaN, deltaX, nu);

	// this will return a pair of value bl and bu
	pair<double, double> pairOfBlBu = calculateBlBu
		(sigmaSqrDeltaX, omegaDeltaX, deltaX, deltaTau, riskFreeInterestRate, dividendRate);
	double bl = pairOfBlBu.first;
	double bu = pairOfBlBu.second;

	// initilize lowerDiag, upperDiag, diag for triDiagSolver
	double *lowerDiag = new double[stepX]();
	double *upperDiag = new double[stepX]();
	double *diag = new double[stepX + 1]();

	for (int index1 = 1; index1 <= stepX - 1; index1++)
	{
		lowerDiag[index1] = -bl;
		upperDiag[index1] = -bu;
		diag[index1] = 1 + riskFreeInterestRate * deltaTau + bl + bu + deltaTau / nu
			* (expintVectorLamdaN[index1] + expintVectorLamdaP[stepX - index1]);
	}

	// boundary condition of omega column
	double * omegaVector = new double[stepX + 1]();
	omegaVector[0] = 0;
	omegaVector[stepX] = 0;

	// populate the first instace of omega with option payoff
	for (int index2 = 1; index2 <= stepX - 1; index2++)
	{
		double currentXn = lowerBoundX + deltaX * index2;
		omegaVector[index2] = populateOptionPayoff(strikePrice, currentXn);
	}

	// use triDiagSolver to get the result
	for (int index3 = 1; index3 <= stepTime; index3++) {
		calcRMatrixAndAddToOmega(omegaVector, expintVectorLamdaN, expintVectorLamdaP, nu, lamdaN, lamdaP,
			expLamdaN, expLamdaP, deltaX, deltaTau, stepX);
		triDiagSolver(lowerDiag, diag, upperDiag, omegaVector, stepX - 1);
	}

	// get the most closest two prices, and calculate its weighted average 
	double stepsInDouble = (log(spotPrice) - lowerBoundX) / deltaX;
	double optionPrice = calcOptionPrice(omegaVector, stepsInDouble);
	
	cout << "The option price is: " << optionPrice << endl;

	// get execution time taken for this run
	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";

	delete[] expLamdaN;
	delete[] expLamdaP;
	delete[] expintVectorLamdaN;
	delete[] expintVectorLamdaP;
	delete[] lowerDiag;
	delete[] upperDiag;
	delete[] diag;
	delete[] omegaVector;
}
