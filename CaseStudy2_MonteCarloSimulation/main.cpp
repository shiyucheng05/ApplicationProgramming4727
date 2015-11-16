#include "functions.h"

int main()
{
	char useDefaultConfig = 'N';
	char anotherRun = 'Y';
	const int nDefaultSimPath = 6;
	const int nDefaultNumTimeInvl = 5;

	int defaultNumSimPath[nDefaultSimPath] = { 200000, 500000, 1000000, 2000000, 5000000, 10000000 };
	int defaultNumTimeInvl[nDefaultNumTimeInvl] = { 10, 20, 50, 100, 200 };
	
	int nSimulationPath = 0;
	int nTimeStep = 0;

	while (anotherRun != 'N' && anotherRun != 'n')
	{
		cout << "Do you want to use default configurations? (Y/N)" << endl;
		cin >> useDefaultConfig;
	
		if (useDefaultConfig == 'Y' || useDefaultConfig == 'y')
		{
			cout << "Using default config now..." << endl;
			cout << "----- The Number of Time Step is set to " << defaultNumTimeInvl[2] << endl;
			for (int indexSimPath = 1; indexSimPath <= nDefaultSimPath; indexSimPath++)
			{
				cout << "***** Round " << indexSimPath << " *****" << endl;
				calcOptionPremium(defaultNumSimPath[indexSimPath - 1], defaultNumTimeInvl[2]);
			}

			cout << "----- The Number of Time Step is set to " << defaultNumTimeInvl[4] << endl;
			for (int indexSimPath = 1; indexSimPath <= nDefaultSimPath; indexSimPath++)
			{
				cout << "***** Round " << indexSimPath << " *****" << endl;
				calcOptionPremium(defaultNumSimPath[indexSimPath - 1], defaultNumTimeInvl[4]);
			}

			cout << "----- The Number of Simulation Path is set to " << defaultNumSimPath[3] << endl;
			for (int indexTimeInvl = 1; indexTimeInvl <= nDefaultNumTimeInvl; indexTimeInvl++)
			{
				cout << "***** Round " << indexTimeInvl << " *****" << endl;
				calcOptionPremium(defaultNumSimPath[3], defaultNumTimeInvl[indexTimeInvl - 1]);
			}
		}
		else 
		{
			cout << "Please specify Number of Simulation Path:" << endl;
			cin >> nSimulationPath;
			cout << "Please specify Number of Time Steps:" << endl;
			cin >> nTimeStep;
			cout << "Calculating now..." << endl;
			calcOptionPremium(nSimulationPath, nTimeStep);
		}

		cout << "Calculate another one? (Y/N):";
		cin >> anotherRun;
	}
	return 0;
}