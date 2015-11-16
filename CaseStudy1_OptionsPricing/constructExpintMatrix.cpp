// Created by Yucheng Shi ys2734

#include "functions.h"

// vector to take into main
double *constructExpintVector(double lamda, int step, double deltaX)
{
	double *expintVector = new double[step + 1]();
	double deltaXMultiplyLamda = deltaX*lamda;

	// put nothing in the expintMatrix[0]
	for (int index = 1; index < step + 1; index++) 
	{
		expintVector[index] = expint(index * deltaXMultiplyLamda);
	}
	return expintVector;
}
