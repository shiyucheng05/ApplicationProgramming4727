#include "functions.h"

void calcOptionPremium(int nSimulationPath, int nTimeStep)
{
	// start the clock to count the execution time
	clock_t start, end;
	start = clock();

	// seeds for normal and gamma distribution
	long normSeed = -12765;
	long gammaSeed = -12765;

	double maturityLength = 0.25;
	double timeInterv = maturityLength / nTimeStep;
	double nu = 0.14;
	double theda = -0.13;
	double sigma = 0.2;
	double riskFreeInterestRate = 0.25 / 100;
	double dividendRate = 1.5 / 100;

	double lowerBarrierLog = log(1600);
	double initSpotPriceLog = log(1975);
	double strike = 1800;

	double accumulativePayoff = 0;
	double omega = 1 / nu * log(1 - theda*nu - sigma*sigma*nu / 2);
	double constantValue = (riskFreeInterestRate - dividendRate) * timeInterv + omega * timeInterv;

	double *spotPricesLog = new double[nTimeStep + 1]();
	spotPricesLog[0] = initSpotPriceLog;

	for (int indexSimPath = 1; indexSimPath <= nSimulationPath; indexSimPath++)
	{
		// flag to indicate if price is ever under a barrier
		int isUnderLowerBarrier = 0;
		for (int indexTimeStep = 1; indexTimeStep <= nTimeStep; indexTimeStep++)
		{
			double normDistSample = invNormal(ran2_mod(&normSeed));
			double gamRandSample = gamrand(timeInterv / nu, nu, &gammaSeed);
			double x = theda * gamRandSample + sigma * sqrt(gamRandSample) * normDistSample;
			spotPricesLog[indexTimeStep] = spotPricesLog[indexTimeStep - 1] + constantValue + x;
			if (spotPricesLog[indexTimeStep] < lowerBarrierLog)
			{
				// set the flat to 1
				isUnderLowerBarrier = 1;
			}
		}

		if (isUnderLowerBarrier == 0)
		{
			// when the payoff is positive
			if (strike - exp(spotPricesLog[nTimeStep]) > 0)
			{
				// accumulate the payoff
				accumulativePayoff = accumulativePayoff + strike - exp(spotPricesLog[nTimeStep]);
			}
		}
	}

	delete[] spotPricesLog;	
	// average of accumulative sum times discount factor
	double optionPremium = accumulativePayoff / nSimulationPath * exp(-riskFreeInterestRate * maturityLength);
	cout << "The option price is: " << optionPremium << endl;
	cout << "When Number of Simulation Path is: " << nSimulationPath << endl;
	cout << "     Number of Time Step is: " << nTimeStep << endl;

	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
}